cmake_minimum_required(VERSION 3.15)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project main.cpp BinarySerialization.cpp BinarySerialization.h TestClass.cpp TestClass.h XMLSerialization.cpp XMLSerialization.h tinyxml2.cpp tinyxml2.h)