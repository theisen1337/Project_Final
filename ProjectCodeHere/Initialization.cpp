#include "Initialization.h"

using namespace std;

//static Computation computation;
//static VulkanRender render;
//static VulkanView view;

static bool isPaused;

bool * Initialization::getBool()
{
	return &isPaused;
}

void Initialization::setBool(bool in)
{
	isPaused = in;
}

//Computation* Initialization::getComputation()
//{
//	//return &computation;
//}
//
//VulkanRender* Initialization::getRender()
//{
//	//return &render;
//}
//
//VulkanView* Initialization::getView()
//{
//	//return &view;
//}