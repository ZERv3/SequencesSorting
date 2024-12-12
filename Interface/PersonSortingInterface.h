#pragma once

#include "../Sequences/Sequence.h"
#include "../Tests/Person.h"
#include "../Tests/Extractor.h"

// Компараторы для Extractor<Person>
bool CompareExtractorFirstName(const Extractor<Person>& a, const Extractor<Person>& b);
bool CompareExtractorLastName(const Extractor<Person>& a, const Extractor<Person>& b);
bool CompareExtractorId(const Extractor<Person>& a, const Extractor<Person>& b);
bool CompareExtractorHeight(const Extractor<Person>& a, const Extractor<Person>& b);

// Загрузка данных Person из файла в последовательность Extractor<Person>
bool LoadPersonsFromFile(const std::string& filename, Sequence<Extractor<Person>>& sequence);

// Сохранение данных Person из последовательности Extractor<Person> в CSV
bool SavePersonsToCSV(const std::string& filename, Sequence<Extractor<Person>>& sequence);

// Интерфейс сортировки Person через Extractor
void RunPersonSortingInterface();