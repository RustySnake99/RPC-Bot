mod bridge;

pub use bridge::compute_best_move;
use pyo3::prelude::*;

#[pyfunction]
fn choose_move(state_json: &str) -> PyResult<String> {
    Ok(compute_best_move(state_json))
}

#[pymodule]
fn showdown_bridge(_py: Python, m: &Bound<'_, PyModule>) -> PyResult<()> {
    m.add_function(wrap_pyfunction!(choose_move, m)?)?;
    Ok(())
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn cpp_call() {
        let result = compute_best_move("{}");
        assert_eq!(result, "{\"move\": \"tackle\"}");
    }
}