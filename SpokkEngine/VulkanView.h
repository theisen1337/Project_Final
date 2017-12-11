#ifndef VULKANVIEW_H
#define VULKANVIEW_H

// Includes GLFW
#define GLFW_INCLUDE_VULKAN 
// Vulkan Header from LunarG SDK which Provides:
// - Functions
// - Structures
// - Enumerations
// Replaces '<vulkan/vulkan.h>'
#include <GLFW/glfw3.h>

// Included for Reporting and Propagating Errors (1/2)
#include <iostream>
// Included for Reporting and Propagating Errors (2/2)
#include <stdexcept>
// Used to allow 'max' and 'min' functions
#include <algorithm>
// Allows us to Replace our Arrays with Vectors for Dynamics
#include <vector>
// Used to Include 'strcmp' in Layer Validation
#include <cstring>
// Used to Create a Set of all Unique Queue Families
#include <set>

const std::vector<const char*> validationLayers = 
{
	"VK_LAYER_LUNARG_standard_validation"
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

	// CONSTRUCTOR //
	VulkanView();
	~VulkanView();

	// GETTERS //
	GLFWwindow* getWindow();
	VkInstance getInstance();
	VkDebugReportCallbackEXT getCallback();
	VkDevice getDevice();
	VkSurfaceKHR getSurface();

	// Width of Window
	static int const WIDTH = 800;
	// Height of Window
	static int const HEIGHT = 600;

	const std::vector<const char*> validationLayers =
	{
		"VK_LAYER_LUNARG_standard_validation"
	};

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
};
#endif