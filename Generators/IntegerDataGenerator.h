#pragma once

// Функция генерации случайных чисел и записи в файл
// minVal, maxVal - диапазон значений (включительно)
// count - количество генерируемых чисел
// Возвращает true при успешной записи, false при неудаче.
bool GenerateIntegersToFile(int minVal, int maxVal, int count, const std::string& filename);