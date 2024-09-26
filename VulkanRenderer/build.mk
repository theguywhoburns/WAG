ifeq ($(wildcard target/release),target/release)
include target/release/libVulkanRenderer.d
LIB_DIR := target/release
else
include target/debug/libVulkanRenderer.d
LIB_DIR := target/debug
endif

all: ${LIB_DIR}/libVulkanRenderer.so  ${CURDIR}/generate_definitions.py
	@echo "Building VulkanRenderer"
	python3 ${CURDIR}/generate_definitions.py
	@cargo build --manifest-path ${CURDIR}/Cargo.toml
	cp ${LIB_DIR}/libVulkanRenderer.so ../bin/libVulkanRenderer.so