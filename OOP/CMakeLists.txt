add_executable (OOP "OOP.cpp" "User.hpp" "User.cpp")

include_directories("Fraction")
include_directories("Containers")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OOP PROPERTY CXX_STANDARD 23)
endif()
