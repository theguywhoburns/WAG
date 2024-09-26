#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![allow(non_upper_case_globals)]
use crate::renderer_interface_bindings::*;
use crate::vulkan::{self};
#[no_mangle]
pub unsafe extern "C" fn RendererInitialize(
        engine: *mut WAG,
        renderer: *mut RendererInterface,
        window_handle: *mut ::std::os::raw::c_void,
    ) -> () {
	vulkan::RendererInitialize(engine, renderer, window_handle)
}
#[no_mangle]
pub unsafe extern "C" fn RendererUpdate(engine: *mut WAG, renderer: *mut RendererInterface) -> () {
	vulkan::RendererUpdate(engine, renderer)
}
#[no_mangle]
pub unsafe extern "C" fn RendererShutdown(engine: *mut WAG, renderer: *mut RendererInterface) -> () {
	vulkan::RendererShutdown(engine, renderer)
}
#[no_mangle]
pub unsafe extern "C" fn RendererGetInterface(data_size: *mut usize) -> RendererInterface {
	vulkan::RendererGetInterface(data_size)
}