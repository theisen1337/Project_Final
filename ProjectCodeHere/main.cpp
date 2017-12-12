#include "VulkanView.h";

int main() {
	VulkanView app;

	try {
		app.Run();
	}
	catch (const std::runtime_error& e) {
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}

<<<<<<< HEAD:ProjectCodeHere/main.cpp
	//...
	//}

	//...Hey matey mate
	//blah
	//}	


    return 0;
}

void render() {
	//Render Placeholder and GitHub Test - Taylor Thomas
=======
	return EXIT_SUCCESS;
>>>>>>> Project_final(David-King):main.cpp
}