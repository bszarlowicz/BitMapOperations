#include "Functions.h"

bool** fun_create2DimArray(unsigned row, unsigned col)
{
	bool** array = nullptr;
	try
	{
		array = new bool* [row];
	}
	catch (const std::bad_alloc)
	{
		std::cerr << "\n Error with creating an array" << std::endl;
		std::cin.ignore();
		exit(0);
	}
	for (unsigned i = 0; i < row; i++)
	{
		try
		{
			array[i] = new bool[col];
		}
		catch (const std::bad_alloc)
		{
			std::cerr << "\n Error with creating an array" << std::endl;
			std::cin.ignore();
			exit(0);
		}
	}

	return array;
}