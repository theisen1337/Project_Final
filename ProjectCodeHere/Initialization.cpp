#include "Initialization.h"
#include <ctype.h>

using namespace std;

//static Computation computation;
//static VulkanRender render;
//static VulkanView view;

static bool Key_P = false;
static bool Key_R = false;
static bool Key_UP_Arrow = false;
static bool Key_Down_Arrow = false;
static bool Key_Left_Arrow = false;
static bool Key_Right_Arrow = false;

bool * Initialization::getBool(char C)
{
	bool catchKey = false;
	C = toupper(C);
	switch (C)
	{
	case'P': return &Key_P;
	case'R': return &Key_R;
	case'^': return &Key_UP_Arrow;
	case'.': return &Key_Down_Arrow;
	case'<': return &Key_Left_Arrow;
	case'>': return &Key_Right_Arrow;
	}
	return &catchKey;
	
}

void Initialization::setBool(bool in,char C)
{
	C = toupper(C);
	switch (C)
	{
	case'P': Key_P = in; break;
	case'R': Key_R = in; break;
	case'^': Key_UP_Arrow = in; break;
	case'.': Key_Down_Arrow = in; break;
	case'<': Key_Left_Arrow = in; break;
	case'>': Key_Right_Arrow = in; break;
	}

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