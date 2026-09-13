#[cxx::bridge]
mod ffi {
    unsafe extern "C++" {
        include!("engine.h");
        fn compute_best_move_cpp(state_json: &str) -> String;
    }
}

pub fn compute_best_move(state_json: &str) -> String {
    ffi::compute_best_move_cpp(state_json)
}