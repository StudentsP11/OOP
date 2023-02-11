#include <iostream>

#include <LinkedList.hpp>

int main()
{
	LinkedList list{ 1,2,3,4 };
	list.pop(0);

	std::cout << list[0];

	return 0; 
}