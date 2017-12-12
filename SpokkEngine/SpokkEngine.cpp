#include "SpokkEngine.h"
#include "VulkanView.h"
#include "VulkanRender.h"

// DECLARES OUR CLASS OBJECTS
static VulkanView view;
static VulkanRender render;

// RETRIEVES CLASS OBJECTS
// First One Makes SpokkEngine a Singleton
SpokkEngine& SpokkEngine::getInstance()
{
	static SpokkEngine instance;

	return instance;
}
VulkanView *SpokkEngine::getView()
{
	return &view;
}
VulkanRender *SpokkEngine::getRender()
{
	return &render;
}

// DECLARES OUR MAIN OBJECT
SpokkEngine app = SpokkEngine::getInstance();

// ############ //
// Runs Program //
// ############ //
void SpokkEngine::run()
{
	// Initiates the Main Window for Viewing
	view.initWindow();

	// Initiates All the Functions
	SpokkEngine::initVulkan();

	// Loop for Rendering
	SpokkEngine::mainLoop();

	// Deletes and Deallocates Memory
	SpokkEngine::cleanup();
}

// ################## //
// Main Run Functions //
// ################## //
void SpokkEngine::initVulkan()
{
	view.createInstance();
	view.setupDebugCallback();
	view.createSurface();
	view.pickPhysicalDevice();
	view.createLogicalDevice();
	view.createSwapChain();
	view.createImageViews();
	render.createGraphicsPipeline();
}

void SpokkEngine::mainLoop()
{
	while (!glfwWindowShouldClose(view.getWindow()))
	{
		// Checks for Events Such as Clicking the 'X' on the Window
		glfwPollEvents();
	}
}

void SpokkEngine::cleanup()
{
	vkDestroyPipelineLayout(view.getDevice(), render.getPipelineLayout(), nullptr);

	for (auto imageView : view.getSwapChainImageViews())
	{
		vkDestroyImageView(view.getDevice(), imageView, nullptr);
	}

	vkDestroySwapchainKHR(view.getDevice(), view.getSwapChain(), nullptr);

	vkDestroyDevice(view.getDevice(), nullptr);

	view.DestroyDebugReportCallbackEXT(view.getInstance(), view.getCallback(), nullptr);

	vkDestroySurfaceKHR(view.getInstance(), view.getSurface(), nullptr);

	vkDestroyInstance(view.instance, nullptr);

	glfwDestroyWindow(view.getWindow());

	glfwTerminate();
}


int main()
{
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