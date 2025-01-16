#pragma once

#include <iostream>
#include <ctime>
#include <memory>
#include <fstream>

#include "../Cache/LRUCache.h"
#include "../Sequences/Sequence.h"
#include "Person.h"

const int CACHE_SIZE = 10;
const int PERSON_COUNT = 10;

void runCacheOperations();
// Вывести на экран содержимое кэша
void printCache(LRUCache<int, int>& cache);

// Вывести содержимое кэша в файл
void writeToFile(LRUCache<int, int>& cache);

// Измерить время работы с кэшем
void measureTimeForCache(LRUCache<int, int>& cache);

// Измерить время работы с объектами типа Person
void measureTimeForPerson(Person person[]);




