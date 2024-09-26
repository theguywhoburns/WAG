#![allow(
    dead_code,
    unused_variables,
    unused_imports,
    non_snake_case,
    non_camel_case_types,
    non_upper_case_globals
)]
// WAG Structs and interfaces
use crate::renderer_interface_bindings::*;

// C stuff
use std::{collections::HashSet, ffi::*, fs::File};

use loader::{LibloadingLoader, LIBRARY};
use vk::{ApplicationInfo, EntryV1_0, HasBuilder, LayerProperties, StringArray};
// Vulkan stuff
use vulkanalia::*;

struct VulkanRendererInternals {
    entry: Entry,
    instance: Instance,
    #[cfg(debug_assertions)]
    debug_utils: vk::DebugUtilsMessengerEXT,
    window_handle: *mut c_void, // We keep the window handle here too
    surface: vk::SurfaceKHR, // We keep the surface handle here
    physical_device: vk::PhysicalDevice,
    device: Device,
    swapchain: vk::SwapchainKHR,
    swapchain_images: Vec<vk::Image>,
    log_file_writer: std::io::BufWriter<File>,
}

/// Whether the validation layers should be enabled.
const VALIDATION_ENABLED: bool = cfg!(debug_assertions);
/// The name of the validation layers.
const VALIDATION_LAYER: vk::ExtensionName = vk::ExtensionName::from_bytes(b"VK_LAYER_KHRONOS_validation");

/// The required device extensions.
const DEVICE_EXTENSIONS: &[vk::ExtensionName] = &[vk::KHR_SWAPCHAIN_EXTENSION.name];
/// The Vulkan SDK version that started requiring the portability subset extension for macOS.
const PORTABILITY_MACOS_VERSION: Version = Version::new(1, 3, 216);

/// The maximum number of frames that can be processed concurrently.
const MAX_FRAMES_IN_FLIGHT: usize = 2;

pub unsafe fn RendererGetInterface(
    data_size: *mut usize,
) -> RendererInterface {
    *data_size = std::mem::size_of::<VulkanRendererInternals>();
    return RendererInterface {
        Initialize: Some(RendererInitialize),
        Update: Some(RendererUpdate),
        Shutdown: Some(RendererShutdown),
        data: std::ptr::null_mut(),
    };
    
}

pub unsafe extern "C" fn RendererInitialize(engine: *mut WAG, renderer: *mut RendererInterface, window_handle: *mut ::std::os::raw::c_void) -> () {
    let internals = &mut*((*renderer).data as *mut VulkanRendererInternals);
    let loader = LibloadingLoader::new(LIBRARY).unwrap();
    internals.log_file_writer = std::io::BufWriter::new(File::create("VulkanRenderer.log").unwrap());
    pretty_env_logger::init();
    internals.entry = Entry::new(loader).unwrap();
    let instance : Instance;
}

pub unsafe extern "C" fn RendererUpdate(
        engine: *mut WAG, 
        renderer: *mut RendererInterface,
    ) -> () {
    
}

pub unsafe extern "C" fn RendererShutdown(engine: *mut WAG, renderer: *mut RendererInterface) -> () {
    
}

unsafe fn create_instance(entry: &vulkanalia::Entry) -> Result<Instance> {
    let application_info = vk::ApplicationInfo::builder()
        .application_name(b"WAG Vulkan Renderer\0")
        .application_version(vk::make_version(1, 0, 0))
        .engine_name(b"WAG\0")
        .engine_version(vk::make_version(1,0,0))// NOT SUPPORTED
        .api_version(vk::make_version(1, 0, 0)); // TODO: Use latest API version
    // Layers

    let available_layers = entry
        .enumerate_instance_layer_properties()
        .unwrap()
        .iter()
        .map(|p| p.layer_name)
        .collect::<HashSet<_>>();
    
    if VALIDATION_ENABLED && !available_layers.contains(&VALIDATION_LAYER) {
        return Err(anyhow!("Validation layer requested but not supported."));
    }

    let layers = if VALIDATION_ENABLED {
        vec![VALIDATION_LAYER.as_ptr()]
    } else {
        Vec::new()
    };

    // Extensions

    let mut extensions = vk_window::get_required_instance_extensions(window)
        .iter()
        .map(|e| e.as_ptr())
        .collect::<Vec<_>>();

    // Required by Vulkan SDK on macOS since 1.3.216.
    let flags = if cfg!(target_os = "macos") && entry.version()? >= PORTABILITY_MACOS_VERSION {
        info!("Enabling extensions for macOS portability.");
        extensions.push(vk::KHR_GET_PHYSICAL_DEVICE_PROPERTIES2_EXTENSION.name.as_ptr());
        extensions.push(vk::KHR_PORTABILITY_ENUMERATION_EXTENSION.name.as_ptr());
        vk::InstanceCreateFlags::ENUMERATE_PORTABILITY_KHR
    } else {
        vk::InstanceCreateFlags::empty()
    };

    if VALIDATION_ENABLED {
        extensions.push(vk::EXT_DEBUG_UTILS_EXTENSION.name.as_ptr());
    }

    // Create

    let mut info = vk::InstanceCreateInfo::builder()
        .application_info(&application_info)
        .enabled_layer_names(&layers)
        .enabled_extension_names(&extensions)
        .flags(flags);

    let mut debug_info = vk::DebugUtilsMessengerCreateInfoEXT::builder()
        .message_severity(vk::DebugUtilsMessageSeverityFlagsEXT::all())
        .message_type(
            vk::DebugUtilsMessageTypeFlagsEXT::GENERAL
                | vk::DebugUtilsMessageTypeFlagsEXT::VALIDATION
                | vk::DebugUtilsMessageTypeFlagsEXT::PERFORMANCE,
        )
        .user_callback(Some(debug_callback));

    if VALIDATION_ENABLED {
        info = info.push_next(&mut debug_info);
    }

    let instance = entry.create_instance(&info, None)?;

    // Messenger

    if VALIDATION_ENABLED {
        data.messenger = instance.create_debug_utils_messenger_ext(&debug_info, None)?;
    }

    Ok(instance)
}