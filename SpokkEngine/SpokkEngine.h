#ifndef SPOKKENGINE_H
#define SPOKKENGINE_H

#define GLFW_INCLUDE_VULKAN 
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>

#include "VulkanView.h"
#include "VulkanRender.h"

using namespace std;

class SpokkEngine
{

public:

	void run();
	void initVulkan();
	void mainLoop();
	void cleanup();

	// INITIALIZER //
	static SpokkEngine& getInstance();

	// GETTERS //
	static VulkanView* getView();
	static VulkanRender* getRender();
};
#endif