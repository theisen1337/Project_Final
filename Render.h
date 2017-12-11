#pragma once

// Includes GLFW
#define GLFW_INCLUDE_VULKAN 

// Vulkan Header from LunarG SDK which Provides:
// - Functions
// - Structures
// - Enumerations
// Replaces '<vulkan/vulkan.h>'
// Includes GLFW
#define GLFW_INCLUDE_VULKAN 
// Allows us to Implement and Use STB Image Library
#define STB_IMAGE_IMPLEMENTATION
// Forces Program to use Radians
#define GLM_FORCE_RADIANS

// Vulkan Header from LunarG SDK which Provides:
// - Functions
// - Structures
// - Enumerations
// Replaces '<vulkan/vulkan.h>'
#include <GLFW/glfw3.h>

// Allows us to use Linear Algebra Types like Vectors and Matrices
#include <glm/glm.hpp>
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
// Allows us to use Arrays
#include <array>
// Can Utilize Time Functions
#include <chrono>

class Render
{
	// Vertex Structure With Two Vertex Shader Attributes
	struct Vertex
{
	// Pulls in the Position and Color from our Vertex Shader
	glm::vec2 pos;
	glm::vec3 color;

	// Structure Describes at Which Rate to Load Data from Memory Throughout the Vertices
	static VkVertexInputBindingDescription getBindingDescription()
	{
		VkVertexInputBindingDescription bindingDescription = {};
		// Specifies Index of the Binding in the Array of Bindings
		bindingDescription.binding = 0;
		// Specifies Number of Bytes from One Entry to the Next
		bindingDescription.stride = sizeof(Vertex);
		// Can have One of Two Values:
		// - VERTEX: Move to the Next Data Entry after Each Vertex
		// - INSTANCE: Move to the Next Data Entry after Each Instance
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

		return bindingDescription;
	}

	// Helper Function to Fill in Vertex Structures
	static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
	{
		// Describes How to Extract a Vertex Attribute from a Chunk of Vertex Data
		//      Originating from a Binding Description
		std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};
		// Tells Vulkan from Which Binding the Per-Vertex Data Comes
		attributeDescriptions[0].binding = 0;
		// References the 'location' Directive of Input in the Vertex Shader
		attributeDescriptions[0].location = 0;
		// Describes Type of Data for Attribute:
		// - R32_SFLOAT: float
		// - R32G32_SFLOAT: vec2
		// - R32G32B32_SFLOAT: vec3
		// - R32G32B32A32_SFLOAT: vec4
		// For Format, Amount of Color Channels Should Match Number of Components in Shader Data Type
		// Implicitely Defines the Byte Size of Attribute Data
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		// Specifies the Number of Bytes Since the Start of the Per-Vertex Data to Read From
		// It Loads One Vertex at a Time and the Position Attribute 'pos' is at an offset of 0 bytes
		// This is Auto Calculated using 'offsetof'
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		// These are Used for Color instead of Position
		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}
};

	// Creates a Vector of Vertices for our Object (Can Change Color of Triangle)
	const std::vector<Vertex> vertices = {
	{ { -0.5f, -0.5f },{ 1.0f, 0.0f, 0.0f } },
	{ { 0.5f, -0.5f },{ 0.0f, 1.0f, 0.0f } },
	{ { 0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f } },
	{ { -0.5f, 0.5f },{ 1.0f, 1.0f, 1.0f } }
};

	const std::vector<uint16_t> indices = {
	0, 1, 2, 2, 3, 0
};

	struct UniformBufferObject
{
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

public:
	Render();
	~Render();

private:
	// Creates a RenderPass Object to use the Handle
	VkRenderPass renderPass;

	// Creates Pipeline Object to Store the Handle
	VkPipelineLayout pipelineLayout;

	// Creates the Graphics Pipeline
	VkPipeline graphicsPipeline;

	// Stores the Different Command Buffers
	VkCommandPool commandPool;

	// Creates our Vertex Buffer
	VkBuffer vertexBuffer;

	// Class Member to Store the Handle to the Vertex Buffer Memory
	VkDeviceMemory vertexBufferMemory;

	// Creates our Index Buffer
	VkBuffer indexBuffer;

	// Stores the Handle to the Index Buffer Memory
	VkDeviceMemory indexBufferMemory;

	// Creates our Uniform Buffer
	VkBuffer uniformBuffer;

	// Stores Handle to Uniform Buffer Memory
	VkDeviceMemory uniformBufferMemory;

	// Stores all the Different Command Buffers
	std::vector<VkCommandBuffer> commandBuffers;

	// Creates Two Semaphores (Used to Synchronize Swap Chain Events)
	// ImageAvailable Signals that Image has been Acquired and is Ready for Rendering
	VkSemaphore imageAvailableSemaphore;
	// RenderFinished Signals that Rendering has Finished and Presentation can Happen
	VkSemaphore renderFinishedSemaphore;


};