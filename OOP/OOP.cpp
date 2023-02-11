#include <iostream>

#include <LinkedList.hpp>

int main()
{
	LinkedList list{ 1,2,3,4 };
	list.insert(3, -1);
	list.add(10);
	std::cout << list[5];

	return 0; 
}