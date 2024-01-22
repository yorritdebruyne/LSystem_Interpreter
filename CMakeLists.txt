cmake_minimum_required(VERSION 3.24)
project(LSystem_Interpreter)

set(CMAKE_CXX_STANDARD 17)

##START Library:
# Make available as Library by creating one
add_library(LSystemLib STATIC
        sources/LSystem.cpp sources/Production.cpp Include/LSystemInterpreter.hpp)

# Define header files for library
target_include_directories(LSystemLib PRIVATE "Include/")
##END Library


##START Test suite:
# Create executable for testing:
add_executable(TestSuite testing/main.cpp #main.cpp = used for including Catch2 to include test build and library
                        testing/test.cpp Include/catch.hpp)

# Define header files for TestSuite
target_include_directories(TestSuite PRIVATE "Include/")

# We tell CMake that our TestSuite depends on LSystemLib otherwise we can't use any of the functions we wrote
target_link_libraries(TestSuite PRIVATE LSystemLib)
##END Test suite

