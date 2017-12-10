#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>


//	Sets up GLFW Window, GPU, Swap Chain, Validation Layers, and Image Views for rendering
class VulkanView
{
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	#ifdef NDEBUG
	const bool enableValidationLayers = false;
	#else
	const bool enableValidationLayers = true;
	#endif

	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	struct QueueFamilyIndices {
		int graphicsFamily = -1;
		int presentFamily = -1;

		bool isComplete() {
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	struct SwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities;
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

	public:
		VulkanView();
		VulkanView(const char* title, int, int);
		~VulkanView();
		void Run(); // Creates and displays the window

	private:
		/*/
		 *	Variables
		/*/

		GLFWwindow* window;	// Stores reference to window

		VkInstance instance;
		VkDebugReportCallbackEXT callback;
		VkSurfaceKHR surface;

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE; // Stores reference to GPU
		VkDevice device;

		VkQueue graphicsQueue;
		VkQueue presentQueue;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkImageView> swapChainImageViews;

		const char* title;	// Title of the window
		int width;			// Width of the window	
		int height;			// Height of the window

		/*/
		 *	Functions
		/*/

		//	Initialization	//
		void initWindow(const char* title, int, int);
		void initVulkan();			// Initializes Vulkan features necessary for window
		void mainLoop();			// Handles events of glfw window
		void cleanUp();				// Deletes instances and deallocates memory
		void createInstance();		// Instantiates application
		void createSurface();		// Creates window surface that Vulkan can interact with

		//	GPU Interface	//
		void pickPhysicalDevice();	// Selects GPU that the engine will use
		void createLogicalDevice();	// Creates logical device to interface with physical device
		bool isDeviceSuitable(VkPhysicalDevice device);
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

		//	Swap Chain	//
		void createSwapChain();		// Creates swap chain for loading images
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

		//	Image View	//
		void createImageViews();	// Creates views for swap chain images
		VkImageView createImageView(VkImage image, VkFormat format);

		//	Validation Layer	//
		void setupDebugCallback();	// Readies validation layers
		std::vector<const char*> getRequiredExtensions();
		bool checkValidationLayerSupport();
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT, VkDebugReportObjectTypeEXT, uint64_t, size_t, int32_t, const char*, const char*, void*);

};