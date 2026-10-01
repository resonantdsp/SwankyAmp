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

/// The short commit a build was made from, for the support report: release
/// candidates and the release carry the same version. Empty where git or the
/// repository is missing, as in a source archive.
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
    let commit = git(&["rev-parse", "--short=7", "HEAD"]).unwrap_or_default();
    println!("cargo:rustc-env=SWANKY_AMP_COMMIT={commit}");
    // A commit moves HEAD, or the branch HEAD names.
    let mut watched = vec!["HEAD".to_owned()];
    watched.extend(git(&["symbolic-ref", "-q", "HEAD"]));
    for reference in watched {
        if let Some(path) = git(&["rev-parse", "--git-path", &reference])
            && Path::new(&path).exists()
        {
            println!("cargo:rerun-if-changed={path}");
        }
    }
}
