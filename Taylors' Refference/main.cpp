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
// Allows us to Use Our Vertex and Fragment Shader
#include <fstream>
// Included for Reporting and Propagating Errors (2/2)
#include <stdexcept>
// Used for Lambda Functions When Doing Resource Management
#include <functional>
// Used to allow 'max' and 'min' functions
#include <algorithm>
// Allows us to Replace our Arrays with Vectors for Dynamics
#include <vector>
// Used to Include 'strcmp' in Layer Validation
#include <cstring>
// Used to Create a Set of all Unique Queue Families
#include <set>

// Constants for the Width and Height of the Application Window
const int WIDTH = 800;
const int HEIGHT = 600;

// #########################################################################################################################################################
// Implicitely Enables Range of Useful Diagnostic Validation Layers Instead of Explicitely Specifying Each One
// #########################################################################################################################################################
const std::vector<const char*> validationLayers =
{
	"VK_LAYER_LUNARG_standard_validation"
};

// #########################################################################################################################################################
// A List of All Required Device Extensions (Similar to List of Validation Layers to Enable)
// #########################################################################################################################################################
const std::vector<const char*> deviceExtensions =
{
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

// #########################################################################################################################################################
// Only Enables Validation Layers if Debugging Mode is On
//
// 'NDEBUG' is a Part of the C++ Standard Library.
// #########################################################################################################################################################
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

// #########################################################################################################################################################
// Is Passed Struct from 'setupDebugCallback()' to Create Object
//
// This is Not Auto Loaded as it is an Extension Function.
// Use 'vkGetInstanceProcAddr' to obtain address. 
// This is also Called a Proxy Function.
// #########################################################################################################################################################
VkResult CreateDebugReportCallbackEXT(
	VkInstance instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback)
{
	// Returns 'nullptr' if the function couldn't be loaded
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

// #########################################################################################################################################################
// Cleans up our 'CreateDebugReportCallbackEXT' Directly Above
//
// Must be Explicitely Loaded due to being an Extension Function.
// Also a Proxy Function
// #########################################################################################################################################################
void DestroyDebugReportCallbackEXT(
	VkInstance instance,
	VkDebugReportCallbackEXT callback,
	const VkAllocationCallbacks* pAllocator)
{
	auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}

// Main Structure for Queues
struct QueueFamilyIndices
{
	// A -1 denotes 'Not Found'
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete() {
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

// Main Structure for SwapChains Containing Information Such as:
// - Basic Surface Capabilities (min/max number of images in chain, min/max width and heigh of images)
// - Surface Formats (pixel format, color space)
// - Available Presentation Modes
struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};



// #########################################################################################################################################################
// #########################################################################################################################################################
// THIS     IS     THE     MAIN     CLASS     OF     THE     CODE
// #########################################################################################################################################################
// #########################################################################################################################################################
class HelloTriangleApplication
{
public:

	// #########################################################################################################################################################
	// Runs all the Main Functions of the Program
	//
	// This is called by the 'int main()'
	// #########################################################################################################################################################
	void run()
	{
		// Initiates the Main Window for Viewing
		initWindow();

		// Initiates All the Main Functions (Function Calls)
		initVulkan();

		// This Function is used for Rendering Frames using an Endless Loop that Iterates until Window is Closed
		mainLoop();

		// This Function Deallocates Resources Once the Main Window is Closed
		cleanup();
	}

private:

	// Stores a Reference of the Main Window
	GLFWwindow* window;

	// Class Member that Holds the Handle to the Instance
	VkInstance instance;

	// Class Member that Holds the Handle to the Callback
	VkDebugReportCallbackEXT callback;

	// Object that Represents an Abstract Type of Surface to Present Rendered Images to
	VkSurfaceKHR surface;

	// Class Member Handle to Store Graphics Card
	// Implicitely Destroyed when 'VkInstance' is Destroyed
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

	// Class Member to store Logical Device Handle
	VkDevice device;

	// Class Member Handle to Interface with our Queues
	// Implicitely Cleaned up when Device is Destroyed
	VkQueue graphicsQueue;

	// Member Variable for VkQueue Presentation Handle
	VkQueue presentQueue;

	// Adds a Swapchain Object for Handling
	VkSwapchainKHR swapChain;

	// Store the Handles of the Different Images
	std::vector<VkImage> swapChainImages;

	// Stores the Format of our Swapchain Images
	VkFormat swapChainImageFormat;

	// Stores the Extent of our Swapchain Images
	VkExtent2D swapChainExtent;

	// Creates a Viewing Object to use any 'VkImage'
	std::vector<VkImageView> swapChainImageViews;

	// #########################################################################################################################################################
	// Initializes the Main Window of the Program
	// #########################################################################################################################################################
	void initWindow()
	{
		// Initializes the GLFW Library
		glfwInit();

		// GLFW was Originally Designed for OpenGL
		// This Tells the Window to Not Create an OpenGL Context
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		// Temporarily Disables Resizing of the Window
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		// Initializes the Actual Window
		window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
	}

	// #########################################################################################################################################################
	// Initializes Several Aspects of the Program
	// #########################################################################################################################################################
	void initVulkan()
	{
		// Initializes the Vulkan Library by Creating an Instance
		// This Connects the Application to the Library
		createInstance();

		// Sets up the Callback to Receive Debug Messages from Validation Layers
		setupDebugCallback();

		// Creates a Window Surface for our Vulkan Code to Interact With
		createSurface();

		// Selects the Graphic Cards and Phsical Devices Being Used
		pickPhysicalDevice();

		// Creates a Logical Device for our Physical Device
		createLogicalDevice();

		// Creates the Swap Chain for our Images
		createSwapChain();

		// Creates the Image Viewing Function
		createImageViews();

		// Creates an Graphics Pipeline that Specifies Input and Output FrameBuffers
		createGraphicsPipeline();
	}

	// #########################################################################################################################################################
	// Main Rendering Loop of Application
	// #########################################################################################################################################################
	void mainLoop()
	{
		// Loop Keeps App Running Until Either:
		// A - Error Occurs
		// B - Window is Closed
		while (!glfwWindowShouldClose(window))
		{
			// Checks for Events Such as Clicking the 'X' on the Window
			glfwPollEvents();
		}
	}

	// #########################################################################################################################################################
	// Deletes Instances and Deallocates Memory of Application
	// #########################################################################################################################################################
	void cleanup()
	{
		// Explicitely Destroys all the Image Views
		for (size_t i = 0; i < swapChainImageViews.size(); i++)
		{
			vkDestroyImageView(device, swapChainImageViews[i], nullptr);
		}

		// Destroys our Swap Chain
		vkDestroySwapchainKHR(device, swapChain, nullptr);

		// Destroys our Logical Device
		vkDestroyDevice(device, nullptr);

		// Destroys the our Callback
		DestroyDebugReportCallbackEXT(instance, callback, nullptr);

		// Destroys the Surface Created
		vkDestroySurfaceKHR(instance, surface, nullptr);

		// Destroys the Instance
		// *Always Third to Last for Deletion*
		vkDestroyInstance(instance, nullptr);

		// Destroys the Window
		// *Always Second to Last for Deletion*
		glfwDestroyWindow(window);

		// Terminates GLFW Itself
		// *Always Last for Deletion*
		glfwTerminate();
	}

	// #########################################################################################################################################################
	// Creates an Instance of the Application
	// #########################################################################################################################################################
	void createInstance()
	{
		// Throws an Error if Validation Layers are Unavailable
		if (enableValidationLayers && !checkValidationLayerSupport())
		{
			throw std::runtime_error("Validation Layers Requested, but not Available!");
		}

		// Specifies Parameters for details on our Application
		VkApplicationInfo appInfo = {};
		// Determines the Type of Structure
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		// *Optional* Possible to use 'pNext' as a Pointer to an Extension-Specific Structure (nullptr by default)
		// Determines Name of our Application
		appInfo.pApplicationName = "Hello Triangle";
		// Determines the Version of our Application
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		// Determines the Name of our Engine
		appInfo.pEngineName = "No Engine";
		// Determines Version of our Engine
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		// Determines Version of the Vulkan API
		appInfo.apiVersion = VK_API_VERSION_1_0;

		// Specifies Parameters of a Newly Created Instance
		VkInstanceCreateInfo createInfo = {};
		// Determines the Type of Structure
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		// *Optional* Use 'pNext' as a pointer to an Extension-Specific Structure
		// Pointer to an instance of 'VkApplicationInfo' which helps recognize behavior inherent to app classes
		createInfo.pApplicationInfo = &appInfo;

		// Ensures we have the Extensions and Uses Them
		auto extensions = getRequiredExtensions();
		// Number of Global Extensions to Enable
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		// Pointer to an Vector of 'enabledExtensionCount' Strings Containing Names of Extensions to Enable
		createInfo.ppEnabledExtensionNames = extensions.data();

		// If the Validation Layer Names are Enabled, Then Include Them
		if (enableValidationLayers)
		{
			// Number of Global Layers to Enable
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			// Pointer to an Vector of 'enabledLayerCount' Strings Containing Names of Layers to Enable for Instance
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			// Sets Number of Global Layers to 0
			createInfo.enabledLayerCount = 0;
		}

		// Checks to See if our Instance was Properly Created
		if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to Create Instance!");
		}

		// *Optional* Checks for Extension Support
		/*
		uint32_t extensionCount = 0;
		//*BELOW* Takes pointer to variable that stores number of extensions and an Vector of 'VkExtensionProperties' to store details of extensions
		//First parameter is optional allowing us to filter extensions by specific validation layers
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr); //Requests the number of extensions

		std::vector<VkExtensionProperties> extensions(extensionCount); //Allocate Vector to hold extension details

		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()); //Query the extension details

		std::cout << "Available Extensions: " << std::endl;
		for (const auto& extension : extensions) { // List the name and version of an extension
		std::cout << "\t" << extension.extensionName << std::endl;
		}
		*/
	}

	// #########################################################################################################################################################
	// Callback Is Used to Relay Debug Messages from our Validation Layers
	// #########################################################################################################################################################
	void setupDebugCallback()
	{
		// Automatically Returns if there are No Validation Layers Enabled
		if (!enableValidationLayers) return;

		// Structure that Creates Details about our Callback
		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		// Allows you to Filter Which Types of Messages you want to Receive
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		// Specifies Pointer to the Callback Function
		// Can Pass Pointer to 'pUserData' Field Which Passes Through 'userData' Parameter
		createInfo.pfnCallback = debugCallback;

		// If Unable to Load Callback, Throw an Error
		if (CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
			throw std::runtime_error("failed to set up debug callback!");
		}
	}

	// #########################################################################################################################################################
	// Creates a Window Surface and Lets Our Vulkan Interact with it
	// #########################################################################################################################################################
	void createSurface()
	{
		// *Optional* This Code is if you want Platform-Specific Code
		/*
		// hwnd and hinstance are the handles to the window and the process
		VkWin32SurfaceCreateInfoKHR createInfo;
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		// Gets the raw HWND from the GLFW window object
		createInfo.hwnd = glfwGetWin32Window(window);
		// Reutnrs the HINSTANCE handle of process
		createInfo.hinstance = GetModuleHandle(nullptr);

		// Then creates the function and explicitly loads it.
		auto CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(instance, "vkCreateWin32SurfaceKHR");

		if (!CreateWin32SurfaceKHR || CreateWin32SurfaceKHR(instance, &createInfo, nullptr, &surface) != VK_SUCCESS)
		{
		throw std::runtime_error("failed to create window surface!");
		}
		*/

		// Instead of creating a structure, we can make a simple call to 'glfwCreateWindowSurface'
		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to Create Window Surface!");
		}
	}

	// #########################################################################################################################################################
	// Picks the Physical Device(s) to be Used with Program (GPUs)
	// #########################################################################################################################################################
	void pickPhysicalDevice()
	{
		// Lists and Queries the Amount of Graphics Cards
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

		// Checks if Any Devices on Computer Have Vulkan Support
		if (deviceCount == 0)
		{
			throw std::runtime_error("Failed to Find GPUs with Vulkan Support!");
		}

		// Allocate an Vector to Hold 'VkPhysicalDevice' Handles
		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

		// Checks to See if Physical Devices Meet Requirements Defined in 'isDeviceSuitable' Function
		for (const auto& device : devices)
		{
			if (isDeviceSuitable(device))
			{
				physicalDevice = device;
				break;
			}
		}

		// If There are no Suitable GPUs, Throw an Error
		if (physicalDevice == VK_NULL_HANDLE)
		{
			throw std::runtime_error("Failed to Find a Suitable GPU!");
		}
	}

	// #########################################################################################################################################################
	// Creates a Logical Device for our Physical Device
	// #########################################################################################################################################################
	void createLogicalDevice()
	{
		// Describes Number of Queues we want for a Single Queue Family
		// This Solely Focuses on Queue with Graphics Capabilities
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

		// Creates an Vector of our Unique createInfo Queues
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
		std::set<int> uniqueQueueFamilies = { indices.graphicsFamily, indices.presentFamily };

		float queuePriority = 1.0f;
		for (int queueFamily : uniqueQueueFamilies)
		{
			// Structure Specifying Parameters of a Newly Created Device Queue
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			// Type of the Structure
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			// Integer Indicating Index of the Queue Family to Create on the Device
			// Index corresponds to Index of Element of 'pQueueFamilyProperties' Vector returned 
			//      from 'vkGetPhysicalDeviceQueueFamilyProperties'
			queueCreateInfo.queueFamilyIndex = queueFamily;
			// Integer Specifying Number of Queues to Create in the Family
			queueCreateInfo.queueCount = 1;
			// Vector of 'queueCount' floats specifying priorities of work that will be submitted to 
			//      each created Queue. Influences scheduling of command buffer execution. *Required*
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		// Structure of Device Features such as Geometry Shaders
		VkPhysicalDeviceFeatures deviceFeatures = {};

		// Main Logical Device Structure
		// Similar to 'VkInstanceCreateInfo' except this is all Device Specific
		VkDeviceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		// Determines number of queues from Size of our Queue Vector
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		// Points to our Queue Vector
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.pEnabledFeatures = &deviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
		createInfo.ppEnabledExtensionNames = deviceExtensions.data();

		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else
		{
			createInfo.enabledLayerCount = 0;
		}

		// Parameters are the Physical Device to Interface with, Queue, and Usage Info Specified.
		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to Create Logical Device!");
		}

		// Retrieve Queue Handles for each Queue Family
		// Parameters are the Logical Device, Queue Family, Queue Index, and Pointer to Variable to store Queue Handle In
		vkGetDeviceQueue(device, indices.graphicsFamily, 0, &graphicsQueue);
		vkGetDeviceQueue(device, indices.presentFamily, 0, &presentQueue);
	}

	// #########################################################################################################################################################
	// Creates the Swap Chain for Loading Images
	// #########################################################################################################################################################
	void createSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);

		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);

		// The Number of Images in the Swap Chain (Queue Length)
		// We add one more than the amount to properly function to implement triple buffering
		// Value of 0 for max means there is no limit, which we should watch for
		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
		{
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}

		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		// Specifies amount of layers each image consists of. (Always 1 unless using 3d stereoscopics)
		createInfo.imageArrayLayers = 1;
		// Specifies the Operations We'll Use the Images in the Swap Chain for
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
		uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

		// Specifies How to Handle Swap Chain Images Across Multiple Chains
		if (indices.graphicsFamily != indices.presentFamily)
		{
			// Images can be used Across Multiple Queues without Explicit Ownership Transfers
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			// An Image is Owned by One Queue at a Time and Ownership must be Explicitely Transfered
			// Offers Best Performance
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0;
			createInfo.pQueueFamilyIndices = nullptr;
		}

		// Specify Certain Transform Applied to Images (Flips, Rotations)
		// Set to 'currentTransform' for no transformations
		createInfo.preTransform = swapChainSupport.capabilities.currentTransform;

		// Specifies if alpha channel should be used for blending with other windows
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

		// If True, then we don't care about the color of pixels that are obscured.
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;

		// New Swap Chains should be able to reference the old chain
		createInfo.oldSwapchain = VK_NULL_HANDLE;

		// Throws Error if Unable to Create Blockchain
		if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to Create Swap Chain!");
		}

		// Query the Number of Images in the Swapchain, then resize the container
		//      and call it again to retrieve the handles.
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
		swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());

		swapChainImageFormat = surfaceFormat.format;
		swapChainExtent = extent;
	}

	// #########################################################################################################################################################
	// Function for Viewing any of our Images
	// #########################################################################################################################################################
	void createImageViews()
	{
		// Resize the List to fit all of the Image Views
		swapChainImageViews.resize(swapChainImages.size());

		// Loop that Iterates over all of the Swap Chain Images
		for (size_t i = 0; i < swapChainImages.size(); i++)
		{
			VkImageViewCreateInfo createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			createInfo.image = swapChainImages[i];

			// viewType - allows you to treat images as 1D, 2D, 3D or cube maps
			createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			// format - allows you to format the image data
			createInfo.format = swapChainImageFormat;

			// Allows you to Swizzle the Color Channels Around
			//      So you can map all of the channels to the red channel for monochrome texture
			//      Can also map constant values of 0 and 1 to a channel
			createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

			// Describes what the Image's purpose is and which part of image should be accessed.
			createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			createInfo.subresourceRange.baseMipLevel = 0;
			createInfo.subresourceRange.levelCount = 1;
			createInfo.subresourceRange.baseArrayLayer = 0;
			createInfo.subresourceRange.layerCount = 1;

			// Throws an Error if Cannot Create a View
			if (vkCreateImageView(device, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS)
			{
				throw std::runtime_error("Failed to Create Image Views!");
			}
		}
	}

	// #########################################################################################################################################################
	// Creates the Graphics Pipeline which Specifies Input and Output Framebuffers
	// #########################################################################################################################################################
	void createGraphicsPipeline()
	{

	}

	// #########################################################################################################################################################
	// Evaluate Physical Devices to See if They are Suitable for What We Want
	// #########################################################################################################################################################
	bool isDeviceSuitable(VkPhysicalDevice device)
	{
		// Queries Basic Device Properties Including:
		// - Device Name
		// - Type of Device
		// - Supported Vulkan Version
		VkPhysicalDeviceProperties deviceProperties;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);

		// Queries Optional Features Such As:
		// - Texture Compression
		// - 64 Bit Floats
		// - Multi Viewport Rendering (For VR)
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		// *Optional* Devices Must be Dedicated Graphics Cards Supporting Geometry Shaders
		/*
		bool isDeviceSuitable(VkPhysicalDevice device) {
		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;
		vkGetPhysicalDeviceProperties(device, &deviceProperties);
		vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

		return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
		deviceFeatures.geometryShader;
		}
		*/

		// *Optional* Instead of Checking if Device is Suitable or Not Before Selecting the First One to Appear,
		// this Gives Every Device a Score and Picks the Highest One. This way, you can Favor Dedicated Graphics
		// Cards by Giving them a Higher Score, but Fall Back to Integrated GPU if Need be.
		/*
		// #########################################################################################################################################################
		// Put this within 'pickPhysicalDevice()'
		// #########################################################################################################################################################

		// Use an ordered map to automatically sort candidates by increasing score
		std::multimap<int, VkPhysicalDevice> candidates;

		for (const auto& device : devices) {
		int score = rateDeviceSuitability(device);
		candidates.insert(std::make_pair(score, device));
		}

		// Check if the best candidate is suitable at all
		if (candidates.rbegin()->first > 0) {
		physicalDevice = candidates.rbegin()->second;
		} else {
		throw std::runtime_error("failed to find a suitable GPU!");
		}

		// #########################################################################################################################################################
		// Build the Below Code in a New Function
		// #########################################################################################################################################################

		int rateDeviceSuitability(VkPhysicalDevice device) {
		...

		int score = 0;

		// Discrete GPUs have a significant performance advantage
		if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		score += 1000;
		}

		// Maximum possible size of textures affects graphics quality
		score += deviceProperties.limits.maxImageDimension2D;

		// Application can't function without geometry shaders
		if (!deviceFeatures.geometryShader) {
		return 0;
		}

		return score;
		}
		*/

		// Checks to Ensure the Selected Device can Process the Commands we Require for our Application
		QueueFamilyIndices indices = findQueueFamilies(device);

		// Checks to Ensure We have All Our Extensions Supported
		bool extensionsSupported = checkDeviceExtensionSupport(device);

		// Check that the Swap Chain Support is Adequate
		bool swapChainAdequate = false;
		if (extensionsSupported)
		{
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}

		// Using This Return will Just Grap Any GPU Available
		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}

	// #########################################################################################################################################################
	// Checks to See if We Have All the Required Extensions (Enumerates Extensions)
	// #########################################################################################################################################################
	bool checkDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

		// Set of Strings to Represent Unconfirmed Required Extensions
		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

		for (const auto& extension : availableExtensions)
		{
			requiredExtensions.erase(extension.extensionName);
		}

		return requiredExtensions.empty();
	}

	// #########################################################################################################################################################
	// Checks for All the Different Queue Families Needed
	//
	// Returns Indices of the Queue Families That Satisfy Specified Properties
	// To best due this, we use the 'QueueFamilyIndices' structure
	// #########################################################################################################################################################
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;

		// Retrieves the List of Queue Families and How Many There Are
		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

		// Contains Details about Queue Families Such As:
		// - Type of Operations Supported
		// - Number of Queues That can be Created
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

		// Loops to Find at Least One Queue Family that Supports 'VK_QUEUE_GRAPHICS_BIT'
		int i = 0;
		for (const auto& queueFamily : queueFamilies)
		{
			if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
			{
				indices.graphicsFamily = i;
			}

			// Looks for Queue Family with Capability of Presenting to our Window Surface
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

			// Check Value of Boolean and Store Presentation Family Queue Index
			if (queueFamily.queueCount > 0 && presentSupport)
			{
				indices.presentFamily = i;
			}

			if (indices.isComplete())
			{
				break;
			}

			i++;
		}

		return indices;
	}

	// #########################################################################################################################################################
	// Returns the Required List of Extensions Based on Whether Validation Layers are Enabled or Not
	// #########################################################################################################################################################
	std::vector<const char*> getRequiredExtensions()
	{
		std::vector<const char*> extensions;

		unsigned int glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		// Extensions Specified by GLFW are Always Required
		for (unsigned int i = 0; i < glfwExtensionCount; i++)
		{
			extensions.push_back(glfwExtensions[i]);
		}

		// Debug Report Extensions are Conditionally Added (Only if Available)
		if (enableValidationLayers)
		{
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return extensions;
	}

	// #########################################################################################################################################################
	// Populates our SwapChainSupportDetails Structure with Basic Information
	// #########################################################################################################################################################
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device)
	{
		SwapChainSupportDetails details;

		// Takes our Device and Window Surface into Account when Determining Support Capabilities
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

		// Query the Supported Surface Formats
		uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

		if (formatCount != 0)
		{
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
		}

		// Query the Supported Presentation Modes
		uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

		if (presentModeCount != 0)
		{
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
		}

		return details;
	}

	// #########################################################################################################################################################
	// Determines the Surface Format or Color Depth of our Swap Chain
	//
	// 'VkSurfaceFormatKHR' contains both 'format' and 'colorSpace' members
	// format -> Specifies color channels and types. 'VK_FORMAT_B8G8R8A8_UNORM stores B, G, R, and A channels 
	//      in that order with 8 bit integer for total of 32 bits per pixel.
	// colorSpace -> Indicates if the SRGB color space is supported or not with a flag
	// #########################################################################################################################################################
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		// Best Case Scenario: Surface has no preferred format
		if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
		{
			return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
		}

		// If we cannot choose format, then go through list and
		//      see if preferred combination is available
		for (const auto& availableFormat : availableFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				return availableFormat;
			}
		}

		return availableFormats[0];
	}

	// #########################################################################################################################################################
	// Determines the Presentation Mode of our Swap Chain
	//
	// 'VK_PRESENT_MODE_IMMEDIATE_KHR' -> Images are Transferred to the Screen Immediately (-Tearing)
	// 'VK_PRESENT_MODE_FIFO_KHR' -> Take Image from Front of Queue When Display Is Refreshed
	//      and Inserts Rendered Image in the Back. Similar to Vertical Sync. 
	//      Display Refresh is Known as "Vertical Blank"
	// 'VK_PRESENT_MODE_FIFO_RELAXED_KHR' -> Like 'FIFO_KHR' except instead of waiting for the next
	//      vertical blank, the image is transferred immediately. (-Tearing)
	// 'VK_PRESENT_MODE_MAILBOX_KHR' -> Instead of blocking app when queue is full, images queued
	//      are replaced by newer ones. Can be used to implement triple buffering (+No Tearing, +Less Latency)
	// #########################################################################################################################################################
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
	{
		VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

		// Checks to See if 'MAILBOX_KHR' is available as it is the preferred mode
		for (const auto& availablePresentMode : availablePresentModes)
		{
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				return availablePresentMode;
			}
			// Some Drivers Don't Support 'FIFO_KHR', in Which Case Prefer 'IMMEDIATE_KHR'
			else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
			{
				bestMode = availablePresentMode;
			}
		}

		// 'FIFO_KHR' is guaranteed, so if nothing else, just use that
		return bestMode;
	}

	// #########################################################################################################################################################
	// Resolution of Swap Chain Images and (Almost) Always Exactly Equal to Resolution of Window
	// #########################################################################################################################################################
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
		{
			return capabilities.currentExtent;
		}
		// Pick the resolution that best matches the window within minImageExtent and maxImageExtent
		else
		{
			VkExtent2D actualExtent = { WIDTH, HEIGHT };

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
	}

	// #########################################################################################################################################################
	// Checks if All the Requested Validation Layers are Available
	// #########################################################################################################################################################
	bool checkValidationLayerSupport()
	{
		// List all of the Available Extensions
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		// Store All of Those Available Extensions in an Vector
		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		// Checks if All the Layers in 'validationLayers' exist in 'availableLayers'
		for (const char* layerName : validationLayers)
		{
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					break;
				}
			}

			if (!layerFound)
			{
				return false;
			}
		}

		return true;
	}

	// #########################################################################################################################################################
	// Allows You to Pass Your Own Data to the Callback
	// 'VKAPI_ATTR' and 'VKAPI_CALL" Ensure Function has Right Signature
	//
	// VkDebugReportFlagsEXT flags - Specifies Type of Message Which can be a Combination of Flags 
	//      - You would use 'VK_DEBUG_REPORT_X_BIT_EXT' with X = 'INFORMATION' || 'WARNING' || 'PERFORMANCE_WARNING' || 'ERROR' || 'DEBUG'
	// VkDebugReportObjectTypeEXT objType - Specifies the Type of Object that is the Subject of the Message
	// const char* msg - Contains Pointer to the Message Itself
	// void* userData - Pass Your Own Data to the Callback
	// #########################################################################################################################################################
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData)
	{

		std::cerr << "Validation Layer: " << msg << std::endl;

		// Returns a Boolean to Indicate if Vulkan Call that Triggered Validation Layer Message Should be Aborted
		// If True, then Aborted with 'VK_ERROR_VALIDATION_FAILED_EXT'
		// Would only be Used to Test Validation Layers, so Always Return 'VK_FALSE'
		return VK_FALSE;
	}

	// #########################################################################################################################################################
	// This loads the Binary Data from the Shader Files (Vertex and Fragment Shader)
	//
	// Will read all of the bytes from the specified file and return them in
	//      byte array managed by std::vector
	// #########################################################################################################################################################
	static std::vector<char> readFile(const std::string& filename)
	{
		// 'ate' - Start Reading at the End of the File (So we can use 'read position')
		// 'binary' - Read the File as Binary File (Avoids Text Transformations)
		std::ifstream file(filename, std::ios::ate | std::ios::binary);

		// Ensures the File is Able to Open
		if (!file.is_open())
		{
			throw std::runtime_error("Failed to Open File!");
		}

		// Reads the Position to Determine Size of File
		// Allocates a Buffer
		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);

		// Seek to Beginning of the File and Read all Bytes at Once
		file.seekg(0);
		file.read(buffer.data(), fileSize);

		// Closes the File
		file.close();

		// Returns the Buffer
		return buffer;
	}
};

// #########################################################################################################################################################
// #########################################################################################################################################################
// THIS     IS     THE     MAIN     FUNCTION
// #########################################################################################################################################################
// #########################################################################################################################################################
int main()
{
	HelloTriangleApplication app;

	// Runs the Main Application
	// Throws Runtime Exception during Execution if There is a Fatal Error
	try
	{
		app.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}