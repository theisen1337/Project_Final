#include "Initialization.h"

using namespace std;

static Computation computation;
static VulkanRender render;
static VulkanView view;

Computation* Initialization::getComputation()
{
	return &computation;
}

VulkanRender* Initialization::getRender()
{
	return &render;
}

VulkanView* Initialization::getView()
{
	return &view;
}