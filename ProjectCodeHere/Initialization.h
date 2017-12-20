#pragma once

//#include "Computation.h"
//#include "VulkanRender.h"
//#include "VulkanView.h"

//struct QueueFamilyIndices
//{
//	int graphicsFamily = -1;
//	int presentFamily = -1;
//
//	bool isComplete()
//	{
//		return graphicsFamily >= 0 && presentFamily >= 0;
//	}
//};
//
//struct SwapChainSupportDetails
//{
//	VkSurfaceCapabilitiesKHR capabilities;
//	std::vector<VkSurfaceFormatKHR> formats;
//	std::vector<VkPresentModeKHR> presentModes;
//};

class Initialization
{
public:
	Initialization() {};
	~Initialization() {};

	static bool * getBool(char C);
	static void setBool(bool in, char C);

	//static Computation* getComputation();
	//static VulkanRender* getRender();
	//static VulkanView* getView();
};