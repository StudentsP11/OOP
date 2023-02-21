#include <iostream>

#include <ISequence.hpp>
#include <Array.hpp>
#include <DynamicArray.hpp>
#include <Stack.hpp>
#include <Pets.h>

using std::string;

int main()
{
    Economist economist;
    Worker& worker = economist;
    worker.work();
	//Pet pet = new Turtle{1,2};

    //pet->grow();

    //std::cout << ((Turtle*)pet)->shell_thickness_;

    return 0;
}