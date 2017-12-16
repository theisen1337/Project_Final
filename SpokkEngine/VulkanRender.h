#ifndef VULKANRENDER_H
#define VULKANRENDER_H

#define GLFW_INCLUDE_VULKAN 
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

class VulkanRender
{

public:

	// INITIALIZATION //
	void createGraphicsPipeline();
	void createRenderPass();
	void createFramebuffers();
	void createCommandPool();
	void createCommandBuffers();
	void drawFrame();
	void createSemaphores();

	// GETTERS //
	VkPipelineLayout getPipelineLayout();
	VkRenderPass getRenderPass();
	VkPipeline getGraphicsPipeline();
	VkCommandPool getCommandPool();
	VkSemaphore getImageAvailableSemaphore();
	VkSemaphore getRenderFinishedSemaphore();

	struct QueueFamilyIndices
	{
		int graphicsFamily = -1;
		int presentFamily = -1;

		bool isComplete()
		{
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	// READ DATA //
	static std::vector<char> readFile(const std::string& filename);

	// SHADERS //
	VkShaderModule createShaderModule(const std::vector<char>& code);
};
#endif