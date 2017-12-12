#ifndef VULKANRENDER_H
#define VULKANRENDER_H

#define GLFW_INCLUDE_VULKAN 
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <array>
#include <chrono>

class VulkanRender
{

public:

	// INITIALIZATION
	void createGraphicsPipeline();

};
#endif