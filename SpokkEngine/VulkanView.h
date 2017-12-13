#ifndef VULKANVIEW_H
#define VULKANVIEW_H

#define GLFW_INCLUDE_VULKAN 
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

using namespace std;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanView
{

public:
	// CLASS MEMBERS //
	std::vector<VkImage> swapChainImages;

	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_LUNARG_standard_validation"
	};

	const std::vector<const char*> deviceExtensions =
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
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
	static VkImageView getSwapChainImageViewsIndex(int index);
	VkExtent2D getSwapChainExtent();
	VkFormat getSwapChainImageFormat();
	std::vector<VkFramebuffer> getSwapChainFramebuffers();
	static VkFramebuffer getSwapChainFramebuffersIndex(int index);
	VkQueue getGraphicsQueue();
	VkQueue getPresentQueue();
	VkPhysicalDevice getPhysicalDevice();
	
	// DEBUGGING //
	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback);
	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator);
	void setupDebugCallback();
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);

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