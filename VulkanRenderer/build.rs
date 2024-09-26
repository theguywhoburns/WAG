fn main() {
    // Generate bindings using bindgen
    let include_path="../WAG/include/";
    let renderer_interface_header = format!("{}interface/renderer.h", include_path);
    println!("cargo:rerun-if-changed={}", renderer_interface_header);
    bindgen::Builder::default()
        .header(renderer_interface_header)
        .clang_arg(format!("-I{}", include_path))
        .clang_arg(format!("-D{}", "BINDGEN"))
        .generate()
        .expect("Unable to generate bindings")
        .write_to_file("src/renderer_interface_bindings.rs")
        .expect("Couldn't write bindings!");

    // Optionally, run the script to generate empty Rust definitions
    std::process::Command::new("python3")
        .arg("generate_definitions.py")
        .status()
        .expect("Failed to generate Rust definitions");
}