//! Fits the cabinet sections that reproduce its 48 kHz response at the other
//! common rates and writes them as source.

use std::env;
use std::fs;
use std::process::ExitCode;

use swanky_amp::dsp::cabinet_fit;

fn main() -> ExitCode {
    let arguments: Vec<String> = env::args().collect();
    let Some(path) = arguments
        .windows(2)
        .find(|pair| pair[0] == "--data")
        .map(|pair| pair[1].clone())
    else {
        eprintln!("usage: fit-cabinet --data <path>");
        return ExitCode::FAILURE;
    };
    let fitted = match cabinet_fit::fit_all() {
        Ok(fitted) => fitted,
        Err(error) => {
            eprintln!("refused: {error}");
            return ExitCode::FAILURE;
        }
    };
    for fit in &fitted {
        println!(
            "{:>8} Hz: {:>5} iterations, largest error {:.4} dB, largest pole radius {:.6}",
            fit.sample_rate, fit.iterations, fit.max_error_db, fit.max_pole_radius
        );
    }
    if let Err(error) = fs::write(&path, cabinet_fit::source(&fitted)) {
        eprintln!("{path}: {error}");
        return ExitCode::FAILURE;
    }
    ExitCode::SUCCESS
}
