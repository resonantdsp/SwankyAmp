//! The soak command's verdict is what release qualification reads, so its
//! reported figures must be finite and free of tremolo on a healthy amplifier.

use std::process::Command;

fn field<'a>(report: &'a str, key: &str) -> &'a str {
    report
        .split_whitespace()
        .find_map(|token| token.strip_prefix(key)?.strip_prefix('='))
        .unwrap_or_else(|| panic!("soak report has no {key}:\n{report}"))
}

#[test]
fn corrected_init_soak_reports_finite_unmodulated_output() {
    let csv = std::path::Path::new(env!("CARGO_TARGET_TMPDIR")).join("soak-init.csv");
    let output = Command::new(env!("CARGO_BIN_EXE_soak"))
        .args(["run", "--preset", "init", "--path", "corrected"])
        // The baseline is the first third of the run. Three windows of it keep
        // the estimator's window-to-window scatter on stationary noise (0.04
        // to 0.07) from deciding the verdict, as one window did.
        .args(["--seconds", "18", "--window", "2", "--signal", "noise"])
        .arg("--csv")
        .arg(&csv)
        .output()
        .expect("soak runs");
    let report = String::from_utf8_lossy(&output.stdout);
    assert!(
        output.status.success(),
        "soak failed: {report}{}",
        String::from_utf8_lossy(&output.stderr)
    );
    assert_eq!(field(&report, "nonfinite"), "0", "{report}");
    let modulation: f64 = field(&report, "max_modulation")
        .split('@')
        .next()
        .unwrap()
        .parse()
        .unwrap();
    // Stationary noise leaves an estimator floor near 0.06; an audible
    // tremolo of about 1 dB depth reads 0.12.
    assert!(modulation < 0.1, "tremolo on stationary input: {report}");
}
