use std::{env, fs, path::Path};

fn main() {
    let source = Path::new("assets/artwork.pack");
    println!("cargo:rerun-if-changed={}", source.display());
    let bytes = fs::read(source).unwrap_or_default();
    let output = Path::new(&env::var("OUT_DIR").unwrap()).join("artwork.pack");
    fs::write(output, bytes).unwrap();
}
