use std::io::Read;
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicBool, AtomicU64, Ordering};
use std::sync::{Arc, OnceLock, RwLock};
use std::time::{Duration, SystemTime, UNIX_EPOCH};

use serde::{Deserialize, Serialize};

const ENDPOINT: &str = "https://resonantdsp.com/release-notices/swanky-amp.json";
const CATALOGUE_URL: &str = "https://resonantdsp.com/products/swanky-amp/?utm_source=swanky-amp-2&utm_medium=plugin&utm_campaign=release-notice";
const PRODUCT_ID: &str = "SwankyAmp";
const CACHE_INTERVAL: Duration = Duration::from_secs(24 * 60 * 60);
const REQUEST_TIMEOUT: Duration = Duration::from_secs(3);
const MAX_DOCUMENT_BYTES: usize = 4 * 1024;

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct Notice {
    pub version: String,
    pub url: &'static str,
}

/// Where the information panel sends a player who needs more than it holds,
/// tagged like the release notice so the website can tell the visits apart.
pub const LINKS: [(&str, &str); 3] = [
    (
        "Website",
        "https://resonantdsp.com/products/swanky-amp/?utm_source=swanky-amp-2&utm_medium=plugin&utm_campaign=information",
    ),
    (
        "Manual",
        "https://resonantdsp.com/manuals/swanky-amp-free/?utm_source=swanky-amp-2&utm_medium=plugin&utm_campaign=information",
    ),
    (
        "Support",
        "https://resonantdsp.com/support/?utm_source=swanky-amp-2&utm_medium=plugin&utm_campaign=information",
    ),
];

/// The launcher is never awaited and a failure is ignored: the press is a
/// convenience and the editor must not block or report on the user's desktop
/// setup.
pub fn open_in_browser(url: &str) {
    let launcher = if cfg!(target_os = "macos") {
        "open"
    } else if cfg!(target_os = "windows") {
        "explorer"
    } else {
        "xdg-open"
    };
    let _ = std::process::Command::new(launcher).arg(url).spawn();
}

/// A process-shared view of the release notice. Each editor opening schedules
/// a refresh if another worker is not already running; reading the latest
/// result never performs I/O.
#[derive(Clone)]
pub struct Service {
    shared: Arc<Shared>,
    cache: Option<PathBuf>,
    endpoint: Arc<str>,
}

struct Shared {
    state: RwLock<State>,
    refreshing: AtomicBool,
}

#[derive(Clone, Default)]
struct State {
    checked_at: Option<u64>,
    current_version: Option<String>,
}

impl Service {
    pub fn start() -> Self {
        static SERVICE: OnceLock<Service> = OnceLock::new();
        let service = SERVICE
            .get_or_init(|| {
                let cache = dirs::cache_dir().map(|directory| {
                    directory
                        .join("Resonant DSP")
                        .join("Swanky Amp 2")
                        .join("release-notice.json")
                });
                Self::configured(cache, ENDPOINT.into())
            })
            .clone();
        service.schedule(SystemTime::now());
        service
    }

    /// The notice to show now. The worker holds the lock only to swap in a
    /// finished answer, never across I/O, so waiting for it cannot stall the
    /// editor, and a reader never sees a spurious gap mid-refresh.
    pub fn current(&self) -> Option<Notice> {
        self.shared
            .state
            .read()
            .ok()
            .and_then(|state| notice_for(state.current_version.as_deref()))
    }

    #[cfg(test)]
    fn spawn(cache: Option<PathBuf>, endpoint: String, now: SystemTime) -> Self {
        let service = Self::configured(cache, endpoint.into());
        service.schedule(now);
        service
    }

    fn configured(cache: Option<PathBuf>, endpoint: Arc<str>) -> Self {
        Self {
            shared: Arc::new(Shared {
                state: RwLock::new(State::default()),
                refreshing: AtomicBool::new(false),
            }),
            cache,
            endpoint,
        }
    }

    fn schedule(&self, now: SystemTime) {
        let Some(cache) = self.cache.clone() else {
            return;
        };
        if self
            .shared
            .refreshing
            .compare_exchange(false, true, Ordering::AcqRel, Ordering::Acquire)
            .is_err()
        {
            return;
        }
        let shared = Arc::clone(&self.shared);
        let endpoint = Arc::clone(&self.endpoint);
        if std::thread::Builder::new()
            .name("swanky-release-notice".into())
            .spawn(move || {
                refresh(&cache, &endpoint, now, &shared.state);
                shared.refreshing.store(false, Ordering::Release);
            })
            .is_err()
        {
            self.shared.refreshing.store(false, Ordering::Release);
        }
    }
}

#[derive(Clone, Deserialize, Serialize)]
#[serde(rename_all = "camelCase", deny_unknown_fields)]
struct Cache {
    schema_version: u8,
    product_id: String,
    checked_at: u64,
    current_version: Option<String>,
}

#[derive(Deserialize)]
#[serde(rename_all = "camelCase", deny_unknown_fields)]
struct Document {
    schema_version: u8,
    product_id: String,
    current_version: Option<String>,
}

fn refresh(cache_path: &Path, endpoint: &str, now: SystemTime, shared: &RwLock<State>) {
    let now = now
        .duration_since(UNIX_EPOCH)
        .map_or(0, |duration| duration.as_secs());
    let memory = shared
        .read()
        .map_or_else(|_| State::default(), |state| state.clone());
    let disk = read_cache(cache_path);
    let previous = match (memory.checked_at, disk) {
        (Some(memory_time), Some(disk)) if disk.checked_at > memory_time => State {
            checked_at: Some(disk.checked_at),
            current_version: disk.current_version,
        },
        (Some(_), _) => memory,
        (None, Some(disk)) => State {
            checked_at: Some(disk.checked_at),
            current_version: disk.current_version,
        },
        (None, None) => memory,
    };
    replace_state(shared, previous.clone());

    if previous
        .checked_at
        .is_some_and(|checked_at| checked_at <= now && now - checked_at < CACHE_INTERVAL.as_secs())
    {
        return;
    }

    let fetched = fetch(endpoint).and_then(|document| {
        if document.schema_version != 1 || document.product_id != PRODUCT_ID {
            return None;
        }
        match document.current_version {
            Some(version) if stable_version(&version).is_some() => Some(Some(version)),
            Some(_) => None,
            None => Some(None),
        }
    });
    let retained = match fetched {
        Some(current_version) => current_version,
        None => previous.current_version,
    };

    // Store before publishing so an answer the editor can see is already
    // durable, where the cache is writable, for the next process to reuse.
    write_cache(
        cache_path,
        &Cache {
            schema_version: 1,
            product_id: PRODUCT_ID.into(),
            checked_at: now,
            current_version: retained.clone(),
        },
    );
    replace_state(
        shared,
        State {
            checked_at: Some(now),
            current_version: retained,
        },
    );
}

fn fetch(endpoint: &str) -> Option<Document> {
    let agent = ureq::config::Config::builder()
        .timeout_global(Some(REQUEST_TIMEOUT))
        .max_redirects(0)
        .user_agent("")
        .tls_config(
            ureq::tls::TlsConfig::builder()
                .root_certs(ureq::tls::RootCerts::PlatformVerifier)
                .unversioned_rustls_crypto_provider(Arc::new(
                    rustls::crypto::ring::default_provider(),
                ))
                .build(),
        )
        .build()
        .new_agent();
    let mut response = agent.get(endpoint).call().ok()?;
    if response.status().as_u16() != 200 {
        return None;
    }
    let body = response
        .body_mut()
        .with_config()
        .limit(MAX_DOCUMENT_BYTES as u64 + 1)
        .read_to_vec()
        .ok()?;
    (body.len() <= MAX_DOCUMENT_BYTES)
        .then(|| serde_json::from_slice(&body).ok())
        .flatten()
}

fn read_cache(path: &Path) -> Option<Cache> {
    let mut file = std::fs::File::open(path).ok()?;
    if file.metadata().ok()?.len() > MAX_DOCUMENT_BYTES as u64 {
        return None;
    }
    let mut bytes = Vec::new();
    file.by_ref()
        .take(MAX_DOCUMENT_BYTES as u64 + 1)
        .read_to_end(&mut bytes)
        .ok()?;
    if bytes.len() > MAX_DOCUMENT_BYTES {
        return None;
    }
    let cache: Cache = serde_json::from_slice(&bytes).ok()?;
    (cache.schema_version == 1
        && cache.product_id == PRODUCT_ID
        && cache
            .current_version
            .as_deref()
            .is_none_or(|version| stable_version(version).is_some()))
    .then_some(cache)
}

fn write_cache(path: &Path, cache: &Cache) {
    static NEXT_TEMPORARY: AtomicU64 = AtomicU64::new(0);

    let Some(directory) = path.parent() else {
        return;
    };
    let Ok(bytes) = serde_json::to_vec(cache) else {
        return;
    };
    if std::fs::create_dir_all(directory).is_err() {
        return;
    }
    let Some(name) = path.file_name() else {
        return;
    };
    let temporary = directory.join(format!(
        ".{}.{}-{}.tmp",
        name.to_string_lossy(),
        std::process::id(),
        NEXT_TEMPORARY.fetch_add(1, Ordering::Relaxed)
    ));
    let written = std::fs::OpenOptions::new()
        .write(true)
        .create_new(true)
        .open(&temporary)
        .and_then(|mut file| {
            use std::io::Write;
            file.write_all(&bytes)?;
            file.sync_all()
        });
    if written.is_ok() && std::fs::rename(&temporary, path).is_err() {
        let _ = std::fs::remove_file(path);
        let _ = std::fs::rename(&temporary, path);
    }
    let _ = std::fs::remove_file(temporary);
}

fn replace_state(shared: &RwLock<State>, state: State) {
    if let Ok(mut current) = shared.write() {
        *current = state;
    }
}

/// The notice a reported current version earns: one only when it is a stable
/// release newer than this build.
pub(crate) fn notice_for(version: Option<&str>) -> Option<Notice> {
    version
        .filter(|candidate| supersedes(candidate, env!("CARGO_PKG_VERSION")))
        .map(|version| Notice {
            version: version.to_owned(),
            url: CATALOGUE_URL,
        })
}

fn supersedes(candidate: &str, current: &str) -> bool {
    stable_version(candidate)
        .zip(stable_version(current))
        .is_some_and(|(candidate, current)| candidate > current)
}

fn stable_version(version: &str) -> Option<[u64; 3]> {
    let mut parts = version.split('.');
    let mut next = || {
        let part = parts.next()?;
        if part.is_empty()
            || !part.bytes().all(|byte| byte.is_ascii_digit())
            || (part.len() > 1 && part.starts_with('0'))
        {
            return None;
        }
        part.parse().ok()
    };
    let parsed = [next()?, next()?, next()?];
    parts.next().is_none().then_some(parsed)
}

#[cfg(test)]
mod tests {
    use super::*;
    use std::io::{Read, Write};
    use std::net::{Shutdown, TcpListener};
    use std::sync::Mutex;
    use std::sync::atomic::{AtomicU64, AtomicUsize, Ordering};
    use std::thread::JoinHandle;
    use std::time::Instant;

    static NEXT_DIRECTORY: AtomicU64 = AtomicU64::new(0);

    struct TestDirectory(PathBuf);

    impl TestDirectory {
        fn new(name: &str) -> Self {
            let path = std::env::temp_dir().join(format!(
                "swanky-release-notice-{name}-{}-{}",
                std::process::id(),
                NEXT_DIRECTORY.fetch_add(1, Ordering::Relaxed)
            ));
            std::fs::create_dir_all(&path).unwrap();
            Self(path)
        }

        fn cache(&self) -> PathBuf {
            self.0.join("release-notice.json")
        }
    }

    impl Drop for TestDirectory {
        fn drop(&mut self) {
            let _ = std::fs::remove_dir_all(&self.0);
        }
    }

    struct Server {
        endpoint: String,
        requests: Arc<AtomicUsize>,
        request: Arc<Mutex<String>>,
        stop: Arc<AtomicBool>,
        thread: Option<JoinHandle<()>>,
    }

    impl Server {
        fn responding(body: Vec<u8>) -> Self {
            let listener = TcpListener::bind("127.0.0.1:0").unwrap();
            listener.set_nonblocking(true).unwrap();
            let address = listener.local_addr().unwrap();
            let requests = Arc::new(AtomicUsize::new(0));
            let request = Arc::new(Mutex::new(String::new()));
            let request_count = Arc::clone(&requests);
            let captured = Arc::clone(&request);
            let stop = Arc::new(AtomicBool::new(false));
            let should_stop = Arc::clone(&stop);
            let thread = std::thread::spawn(move || {
                let deadline = Instant::now() + Duration::from_millis(750);
                while Instant::now() < deadline && !should_stop.load(Ordering::Relaxed) {
                    match listener.accept() {
                        Ok((mut stream, _)) => {
                            request_count.fetch_add(1, Ordering::Relaxed);
                            let mut bytes = [0; 8 * 1024];
                            let read = stream.read(&mut bytes).unwrap_or(0);
                            *captured.lock().unwrap() =
                                String::from_utf8_lossy(&bytes[..read]).into_owned();
                            let _ = write!(
                                stream,
                                "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nContent-Length: {}\r\nConnection: close\r\n\r\n",
                                body.len()
                            );
                            let _ = stream.write_all(&body);
                        }
                        Err(error) if error.kind() == std::io::ErrorKind::WouldBlock => {
                            std::thread::sleep(Duration::from_millis(2));
                        }
                        Err(_) => return,
                    }
                }
            });
            Self {
                endpoint: format!("http://{address}/current.json"),
                requests,
                request,
                stop,
                thread: Some(thread),
            }
        }

        fn finish(&mut self) {
            self.stop.store(true, Ordering::Relaxed);
            self.thread.take().unwrap().join().unwrap();
        }
    }

    impl Drop for Server {
        fn drop(&mut self) {
            if let Some(thread) = self.thread.take() {
                self.stop.store(true, Ordering::Relaxed);
                thread.join().unwrap();
            }
        }
    }

    fn document(version: Option<&str>) -> Vec<u8> {
        serde_json::json!({
            "schemaVersion": 1,
            "productId": "SwankyAmp",
            "currentVersion": version,
        })
        .to_string()
        .into_bytes()
    }

    fn at(second: u64) -> SystemTime {
        UNIX_EPOCH + Duration::from_secs(second)
    }

    fn wait_for_cache(path: &Path, checked_at: u64) {
        let deadline = Instant::now() + Duration::from_secs(5);
        loop {
            let durable = std::fs::read(path)
                .ok()
                .and_then(|bytes| serde_json::from_slice::<serde_json::Value>(&bytes).ok())
                .and_then(|cache| cache.get("checkedAt")?.as_u64())
                == Some(checked_at);
            if durable {
                return;
            }
            assert!(
                Instant::now() < deadline,
                "the completed cache record was not stored"
            );
            std::thread::sleep(Duration::from_millis(2));
        }
    }

    fn wait_for_notice(service: &Service) -> Notice {
        let deadline = Instant::now() + Duration::from_secs(2);
        loop {
            if let Some(notice) = service.current() {
                return notice;
            }
            assert!(
                Instant::now() < deadline,
                "the newer release was not published"
            );
            std::thread::sleep(Duration::from_millis(2));
        }
    }

    fn wait_for_version(service: &Service, version: &str) -> Notice {
        let deadline = Instant::now() + Duration::from_secs(2);
        loop {
            if let Some(notice) = service.current()
                && notice.version == version
            {
                return notice;
            }
            assert!(
                Instant::now() < deadline,
                "release {version} was not published"
            );
            std::thread::sleep(Duration::from_millis(2));
        }
    }

    #[test]
    fn a_newer_stable_release_uses_the_fixed_tagged_catalogue_and_fresh_cache() {
        let directory = TestDirectory::new("cache");
        let mut first = Server::responding(document(Some("2.0.1")));
        let service = Service::spawn(Some(directory.cache()), first.endpoint.clone(), at(1_000));
        let notice = wait_for_notice(&service);
        assert_eq!(notice.version, "2.0.1");
        assert_eq!(notice.url, CATALOGUE_URL);
        first.finish();

        let mut cached = Server::responding(document(Some("2.0.2")));
        let service = Service::spawn(Some(directory.cache()), cached.endpoint.clone(), at(1_600));
        assert_eq!(wait_for_notice(&service).version, "2.0.1");
        cached.finish();
        assert_eq!(cached.requests.load(Ordering::Relaxed), 0);
    }

    #[test]
    fn malformed_and_prerelease_versions_are_silent_and_start_a_failure_cooldown() {
        let directory = TestDirectory::new("malformed");
        let mut malformed = Server::responding(document(Some("2.0.1-rc.1")));
        let service = Service::spawn(
            Some(directory.cache()),
            malformed.endpoint.clone(),
            at(2_000),
        );
        wait_for_cache(&directory.cache(), 2_000);
        assert_eq!(service.current(), None);
        malformed.finish();

        let mut retry = Server::responding(document(Some("2.0.1")));
        let service = Service::spawn(Some(directory.cache()), retry.endpoint.clone(), at(2_600));
        std::thread::sleep(Duration::from_millis(25));
        assert_eq!(service.current(), None);
        retry.finish();
        assert_eq!(retry.requests.load(Ordering::Relaxed), 0);

        for version in ["2.0", "02.0.1", "v2.0.1", "2.x.1", "2.0.1+meta"] {
            let directory = TestDirectory::new("invalid-version");
            let mut server = Server::responding(document(Some(version)));
            let service =
                Service::spawn(Some(directory.cache()), server.endpoint.clone(), at(3_000));
            wait_for_cache(&directory.cache(), 3_000);
            assert_eq!(service.current(), None, "{version} must not be announced");
            server.finish();
        }
    }

    #[test]
    fn an_offline_check_finishes_promptly_and_the_no_release_document_is_valid() {
        let directory = TestDirectory::new("offline");
        let listener = TcpListener::bind("127.0.0.1:0").unwrap();
        let endpoint = format!("https://{}/current.json", listener.local_addr().unwrap());
        let closer = std::thread::spawn(move || {
            if let Ok((stream, _)) = listener.accept() {
                let _ = stream.shutdown(Shutdown::Both);
            }
        });
        let started = Instant::now();
        let service = Service::spawn(Some(directory.cache()), endpoint, at(4_000));
        wait_for_cache(&directory.cache(), 4_000);
        closer.join().unwrap();
        assert!(started.elapsed() < Duration::from_secs(5));
        assert_eq!(service.current(), None);

        let mut no_release = Server::responding(document(None));
        let other = TestDirectory::new("no-release");
        let service = Service::spawn(Some(other.cache()), no_release.endpoint.clone(), at(4_000));
        wait_for_cache(&other.cache(), 4_000);
        assert_eq!(service.current(), None);
        no_release.finish();
    }

    #[test]
    fn oversized_documents_are_rejected_and_a_future_cache_time_is_rechecked() {
        let oversized_directory = TestDirectory::new("oversized");
        let mut oversized = Server::responding(vec![b' '; MAX_DOCUMENT_BYTES + 1]);
        let service = Service::spawn(
            Some(oversized_directory.cache()),
            oversized.endpoint.clone(),
            at(5_000),
        );
        wait_for_cache(&oversized_directory.cache(), 5_000);
        assert_eq!(service.current(), None);
        oversized.finish();

        let oversized_cache = TestDirectory::new("oversized-cache");
        std::fs::write(oversized_cache.cache(), vec![b' '; MAX_DOCUMENT_BYTES + 1]).unwrap();
        let mut replacement = Server::responding(document(Some("2.0.1")));
        let service = Service::spawn(
            Some(oversized_cache.cache()),
            replacement.endpoint.clone(),
            at(5_000),
        );
        assert_eq!(wait_for_notice(&service).version, "2.0.1");
        replacement.finish();
        assert_eq!(replacement.requests.load(Ordering::Relaxed), 1);

        let directory = TestDirectory::new("future");
        let mut first = Server::responding(document(Some("2.0.1")));
        let service = Service::spawn(Some(directory.cache()), first.endpoint.clone(), at(10_000));
        assert_eq!(wait_for_notice(&service).version, "2.0.1");
        first.finish();

        let mut corrected = Server::responding(document(Some("2.0.2")));
        let service = Service::spawn(
            Some(directory.cache()),
            corrected.endpoint.clone(),
            at(9_000),
        );
        assert_eq!(wait_for_version(&service, "2.0.2").version, "2.0.2");
        corrected.finish();
        assert_eq!(corrected.requests.load(Ordering::Relaxed), 1);
    }

    #[test]
    fn the_request_contains_no_version_identifier_or_query() {
        let directory = TestDirectory::new("request");
        let mut server = Server::responding(document(Some("2.0.1")));
        let service = Service::spawn(Some(directory.cache()), server.endpoint.clone(), at(6_000));
        let _ = wait_for_notice(&service);
        server.finish();
        let request = server.request.lock().unwrap();
        assert!(request.starts_with("GET /current.json HTTP/1.1\r\n"));
        assert!(!request.contains("2.0.0"));
        assert!(!request.contains("?"));
        assert!(!request.to_ascii_lowercase().contains("user-agent:"));
    }

    #[test]
    fn only_a_numerically_newer_stable_version_supersedes_the_running_one() {
        assert!(supersedes("2.0.1", "2.0.0"));
        assert!(supersedes("2.10.0", "2.9.9"));
        assert!(supersedes("3.0.0", "2.99.99"));
        assert!(!supersedes("2.0.0", "2.0.0"));
        assert!(!supersedes("1.9.9", "2.0.0"));
        assert!(!supersedes("2.0.10", "2.1.0"));
        for malformed in ["2.1", "2.1.0.0", "v2.1.0", "2.1.0-rc.1", "", "2..1"] {
            assert!(
                !supersedes(malformed, "2.0.0"),
                "{malformed} must not supersede"
            );
        }
    }

    #[test]
    fn reopening_with_an_unwritable_cache_retains_the_notice_and_attempt_cooldown() {
        let directory = TestDirectory::new("unwritable");
        let blocker = directory.0.join("not-a-directory");
        std::fs::write(&blocker, b"blocks cache directory creation").unwrap();
        let cache = blocker.join("release-notice.json");
        let mut server = Server::responding(document(Some("2.0.1")));
        let service = Service::spawn(Some(cache), server.endpoint.clone(), at(7_000));
        assert_eq!(wait_for_notice(&service).version, "2.0.1");

        for _ in 0..20 {
            service.schedule(at(7_600));
            std::thread::sleep(Duration::from_millis(5));
        }

        assert_eq!(service.current().unwrap().version, "2.0.1");
        assert_eq!(server.requests.load(Ordering::Relaxed), 1);
        server.finish();
    }
}
