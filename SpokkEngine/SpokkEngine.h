#ifndef SPOKKENGINE_H
#define SPOKKENGINE_H

// Includes GLFW
#define GLFW_INCLUDE_VULKAN 
// Vulkan Header from LunarG SDK which Provides:
// - Functions
// - Structures
// - Enumerations
// Replaces '<vulkan/vulkan.h>'
#include <GLFW/glfw3.h>

// Ensures Functions use Radians as Arguments
#define GLM_FORCE_RADIANS
// Allows us to use Linear Algebra Types like Vectors and Matrices
#include <glm/glm.hpp>
// Exposes Functios that can Generate Model Transformations
// - glm::rotate, glm::lookAt
// Can also use Projection Transformations such as glm::perspective
#include <glm/gtc/matrix_transform.hpp>

// Lets us use the STB Image Library to Upload Images
#define STB_IMAGE_IMPLEMENTATION
// Inclues our STB_Image header
#include <stb_image.h>

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
// Exposes Functions to do Precise Timekeeping
#include <chrono>

class SpokkEngine
{
public:

	void run();
	void initVulkan();
	void mainLoop();
	void cleanup();
};
#endif