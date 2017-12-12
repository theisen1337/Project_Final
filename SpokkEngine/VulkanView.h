#ifndef VULKANVIEW_H
#define VULKANVIEW_H

#define GLFW_INCLUDE_VULKAN 
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

const std::vector<const char*> validationLayers = 
{
	"VK_LAYER_LUNARG_standard_validation"
};

const std::vector<const char*> deviceExtensions = 
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanView
{

public:
	// CLASS MEMBERS //
	VkInstance instance;
	VkDebugReportCallbackEXT callback;

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	VkQueue graphicsQueue;
	VkQueue presentQueue;

	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	// CONSTRUCTOR //
	VulkanView();
	~VulkanView();

	// GETTERS //
	GLFWwindow* getWindow();
	VkInstance getInstance();
	VkDebugReportCallbackEXT getCallback();
	VkDevice getDevice();
	VkSurfaceKHR getSurface();
	VkSwapchainKHR getSwapChain();
	std::vector<VkImageView> getSwapChainImageViews();

	// DEBUGGING //
	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
	void setupDebugCallback();

	// OBTAIN EXTENSIONS //
	std::vector<const char*> getRequiredExtensions();

	// CHECK VALIDATION LAYERS //
	bool checkValidationLayerSupport();

	// INITIALIZATION // 
	void initWindow();
	void createInstance();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSurface();
	void createSwapChain();
	void createImageViews();

	// SWAPCHAIN //
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	// CHECK DEVICE //
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	bool isDeviceSuitable(VkPhysicalDevice device);
};
#endif