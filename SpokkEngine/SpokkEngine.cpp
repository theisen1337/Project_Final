#include "SpokkEngine.h"
#include "VulkanView.h"

VulkanView view;

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
	vkDestroyDevice(view.getDevice(), nullptr);

	view.DestroyDebugReportCallbackEXT(view.getInstance(), view.getCallback(), nullptr);

	vkDestroySurfaceKHR(view.getInstance(), view.getSurface(), nullptr);

	vkDestroyInstance(view.instance, nullptr);

	glfwDestroyWindow(view.getWindow());

	glfwTerminate();
}

int main()
{
	SpokkEngine application;

	try
	{
		application.run();
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}