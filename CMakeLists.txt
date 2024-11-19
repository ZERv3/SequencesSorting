cmake_minimum_required(VERSION 3.29)
project(SequencesSorting)

set(CMAKE_CXX_STANDARD 20)

add_executable(SequencesSorting main.cpp
        Sequences/Sequences.h
        Sequences/LinkedList.h
        Sequences/DynamicArray.h
        Sorting/ISorted.h
        Interface/Interface.cpp
        Interface/Interface.h
        Sorting/Sorting.h
        Tests/FileWork.cpp
        Tests/FileWork.h
        Tests/SequenceTest.cpp
        Tests/SequenceTest.h
        Tests/Test.cpp
        Tests/Test.h
)
