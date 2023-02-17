#include <iostream>

#include <ISequence.hpp>
#include <Array.hpp>
#include <DynamicArray.hpp>
#include <Stack.hpp>

using std::string;

int main()
{
	auto arr1 = 
		std::make_unique<Array<int>>(Array{ 1,2,3 });
	
	std::unique_ptr<ISequence<int>> ref = std::move(arr1);

	std::cout << *ref;

	auto stack = std::make_unique<Stack<int>>(Stack{ 1,2,3 });

	std::cout << stack->pop();

	return 0;
}