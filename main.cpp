#include "Visualizer.h"
#include <iostream>

auto main(int argc, char* argv[]) -> int
{

	int x, y;
	switch (argc)
	{
	case 1:
		x = y = 10;
		break;
	case 3:
		x = atoi(argv[1]);
		y = atoi(argv[2]);
		break;
	default:
		std::cout << "Either use no arguments, or give 2 ints to use as map dimensions." << std::endl;
		return -1;
	}
	Visualizer v(x, y);
	v.go();
	return 0;
}