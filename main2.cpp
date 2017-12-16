#include <conio.h>
#include <stdlib.h>
#include <iostream>

#include "Initialization.h"

using namespace std;

int main()
{
	Computation* a = Initialization::getComputation();
	Computation* b = Initialization::getComputation();

	for(int i = 0; i < 100; i++)
	{
		a->Instruction();
		cout << a->getRunTime() << "\t" << b->getRunTime() << endl;
	}
	
	//pause output to be read, continue with any key press.
	cin.get();

	//successful exit
	return EXIT_SUCCESS;
}