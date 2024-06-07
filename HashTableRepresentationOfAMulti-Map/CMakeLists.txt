cmake_minimum_required(VERSION 3.27)
project(Lab4DSA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab4DSA
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h)
