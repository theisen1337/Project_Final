#include "SpokkEngine.h"
#include "VulkanView.h"
#include "VulkanRender.h"
#include "Computation.h"

// DECLARES OUR CLASS OBJECTS
static VulkanView view;
static VulkanRender render;
static Computation Compute;

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
	render.createDescriptorSetLayout();
	render.createGraphicsPipeline();
	render.createCommandPool();
	render.createDepthResources();
	render.createFramebuffers();
	render.createTextureImage(); // <--
	render.createTextureImageView(); // <--
	render.createTextureSampler();
	render.createVertexBuffer();
	render.createIndexBuffer();
	render.createUniformBuffer();
	render.createDescriptorPool();
	render.createDescriptorSet();
	render.createCommandBuffers();
	render.createSemaphores();
}

void SpokkEngine::mainLoop()
{
	while (!glfwWindowShouldClose(view.getWindow()))
	{
		Compute.Instruction();
		glfwSetKeyCallback(view.getWindow(), view.keyCallback);
		/*glfwPollEvents();

		render.updateUniformBuffer();
		render.drawFrame();*/
	}

	vkDeviceWaitIdle(view.getDevice());
}

void SpokkEngine::cleanup()
{
	view.cleanupSwapChain();

	vkDestroySampler(view.getDevice(), render.getTextureSampler(), nullptr);
	vkDestroyImageView(view.getDevice(), render.getTextureImageView(), nullptr);

	vkDestroyImage(view.getDevice(), render.getTextureImage(), nullptr);
	vkFreeMemory(view.getDevice(), render.getTextureImageMemory(), nullptr);

	vkDestroyDescriptorPool(view.getDevice(), render.getDescriptorPool(), nullptr);

	vkDestroyDescriptorSetLayout(view.getDevice(), render.getDescriptorSetLayout(), nullptr);

	vkDestroyBuffer(view.getDevice(), render.getUniformBuffer(), nullptr);
	//vkFreeMemory(view.getDevice(), render.getUniformBuffer(), nullptr);

	vkDestroyBuffer(view.getDevice(), render.getIndexBuffer(), nullptr);
	vkFreeMemory(view.getDevice(), render.getIndexBufferMemory(), nullptr);

	vkDestroyBuffer(view.getDevice(), render.getVertexBuffer(), nullptr);
	vkFreeMemory(view.getDevice(), render.getVertexBufferMemory(), nullptr);

	vkDestroySemaphore(view.getDevice(), render.getRenderFinishedSemaphore(), nullptr);
	vkDestroySemaphore(view.getDevice(), render.getImageAvailableSemaphore(), nullptr);

	vkDestroyCommandPool(view.getDevice(), render.getCommandPool(), nullptr);

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