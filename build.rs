use std::{env, fs, path::Path};

fn main() {
    notices();
    commit();
    let source = Path::new("assets/artwork.pack");
    println!("cargo:rerun-if-changed={}", source.display());
    let bytes = fs::read(source).unwrap_or_default();
    let output = Path::new(&env::var("OUT_DIR").unwrap()).join("artwork.pack");
    fs::write(output, bytes).unwrap();
}

/// Release builds embed the notices `scripts/notices.sh` writes, named by
/// THIRD_PARTY_NOTICES; a development build embeds a pointer to that command
/// instead, so the per-change gate never generates them.
fn notices() {
    println!("cargo:rerun-if-env-changed=THIRD_PARTY_NOTICES");
    let text = match std::env::var("THIRD_PARTY_NOTICES") {
        Ok(path) => {
            println!("cargo:rerun-if-changed={path}");
            std::fs::read_to_string(&path)
                .unwrap_or_else(|error| panic!("THIRD_PARTY_NOTICES={path}: {error}"))
        }
        Err(_) => "This development build carries no third-party notices; \
                   `just notices` writes them."
            .to_owned(),
    };
    let out = std::path::Path::new(&std::env::var("OUT_DIR").unwrap()).join("notices.txt");
    std::fs::write(out, text).unwrap();
}

/// The build number and short commit a build was made from: release
/// candidates and the release carry the same version. The number counts the
/// commits behind HEAD, so it rises with every master commit and needs a full
/// checkout. Where git or the repository is missing, as in a source archive,
/// the number is 0 and the commit "unknown".
fn commit() {
    let git = |args: &[&str]| {
        std::process::Command::new("git")
            .args(args)
            .output()
            .ok()
            .filter(|output| output.status.success())
            .and_then(|output| String::from_utf8(output.stdout).ok())
            .map(|text| text.trim().to_owned())
    };
    let commit = git(&["rev-parse", "--short=7", "HEAD"]).unwrap_or_else(|| "unknown".into());
    println!("cargo:rustc-env=SWANKY_AMP_COMMIT={commit}");
    let build = git(&["rev-list", "--count", "HEAD"])
        .and_then(|count| count.parse::<u32>().ok())
        .unwrap_or(0);
    println!("cargo:rustc-env=SWANKY_AMP_BUILD={build}");
    // Every commit appends to HEAD's reflog, even once `git gc` has packed
    // the branch ref; HEAD itself is the fallback where no reflog is kept.
    let watched = ["logs/HEAD", "HEAD"]
        .into_iter()
        .filter_map(|name| git(&["rev-parse", "--git-path", name]))
        .find(|path| Path::new(path).exists());
    if let Some(path) = watched {
        println!("cargo:rerun-if-changed={path}");
    }
}
