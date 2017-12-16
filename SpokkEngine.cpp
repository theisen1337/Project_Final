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
	initVulkan();

	// Loop for Rendering
	mainLoop();

	// Deletes and Deallocates Memory
	cleanup();
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
	render.createRenderPass();
	render.createGraphicsPipeline();
	render.createFramebuffers();
	render.createCommandPool();
	render.createCommandBuffers();
	render.createSemaphores();
}

void SpokkEngine::mainLoop()
{
	while (!glfwWindowShouldClose(view.getWindow()))
	{
		glfwPollEvents();
		render.drawFrame();
	}
}

void SpokkEngine::cleanup()
{
	vkDestroySemaphore(view.getDevice(), render.getRenderFinishedSemaphore(), nullptr);
	vkDestroySemaphore(view.getDevice(), render.getImageAvailableSemaphore(), nullptr);

	vkDestroyCommandPool(view.getDevice(), render.getCommandPool(), nullptr);

	for (auto framebuffer : view.getSwapChainFramebuffers()) 
	{
		vkDestroyFramebuffer(view.getDevice(), framebuffer, nullptr);
	}

	vkDestroyPipeline(view.getDevice(), render.getGraphicsPipeline(), nullptr);
	vkDestroyPipelineLayout(view.getDevice(), render.getPipelineLayout(), nullptr);
	vkDestroyRenderPass(view.getDevice(), render.getRenderPass(), nullptr);

	for (auto imageView : view.getSwapChainImageViews())
	{
		vkDestroyImageView(view.getDevice(), imageView, nullptr);
	}

	vkDestroySwapchainKHR(view.getDevice(), view.getSwapChain(), nullptr);

	vkDestroyDevice(view.getDevice(), nullptr);

	view.DestroyDebugReportCallbackEXT(view.getInstance(), view.getCallback(), nullptr);

	vkDestroySurfaceKHR(view.getInstance(), view.getSurface(), nullptr);

	vkDestroyInstance(view.getInstance(), nullptr);

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