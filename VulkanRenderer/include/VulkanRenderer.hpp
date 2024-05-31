#pragma once 

#include <vulkan/vulkan.hpp>

#define RENDERER_API __declspec(dllexport)

class VulkanDevice {
public:
	vk::Device handle;
	vk::PhysicalDevice physicalDevice;
};

class VulkanSwapchain {
public:
	vk::SwapchainKHR handle;
};

class VulkanContext {
public:
	
};

