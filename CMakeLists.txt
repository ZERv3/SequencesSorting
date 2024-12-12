cmake_minimum_required(VERSION 3.29)
project(SequencesSorting)

set(CMAKE_CXX_STANDARD 20)

add_executable(SequencesSorting main.cpp
        Sequences/Sequence.h
        Sequences/DynamicArray.h
        Sequences/LinkedList.h
        Sorting/ISorter.h
        Sorting/SortingAlgorithms.h
        Tests/Person.h
        Tests/SequenceFunctionalTests.cpp
        Tests/SequenceStressTests.cpp
        Tests/SequenceStressTests.h
        Tests/SequenceFunctionalTests.h
        Tests/SorterStressTests.cpp
        Tests/SorterStressTests.h
        Tests/SorterFunctionalTests.cpp
        Tests/SorterFunctionalTests.h
        Tests/Extractor.h
        Interface/UI.cpp
        Interface/UI.h
        Interface/PersonSortingInterface.cpp
        Interface/PersonSortingInterface.h
        Generators/IntegerDataGenerator.cpp
        Generators/IntegerDataGenerator.h
        Interface/IntegerSortingInterface.cpp
        Interface/IntegerSortingInterface.h
)
