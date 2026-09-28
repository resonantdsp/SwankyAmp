use std::{env, fs, path::Path};

fn main() {
    notices();
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
