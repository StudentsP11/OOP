add_executable (OOP "OOP.cpp"  "User.hpp" "User.cpp"     "Array/LinkedList.hpp" "Array/Pets.h")

include_directories("Fraction")
include_directories("Array")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OOP PROPERTY CXX_STANDARD 20)
endif()
