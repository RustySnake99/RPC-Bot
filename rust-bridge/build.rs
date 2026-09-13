fn main() {
    cxx_build::bridge("src/bridge.rs").file("../cpp/engine.cpp").include("../cpp").include("../cpp/vendor").std("c++17").compile("engine-bridge");
    
    println!("cargo:rerun-if-changed=../cpp/engine.cpp");
    println!("cargo:rerun-if-changed=src/bridge.rs");
    println!("cargo:rerun-if-changed=../cpp/engine.h");
}