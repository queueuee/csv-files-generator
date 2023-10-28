#pragma once

#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <string>
#include <windows.h>
#include <limits>
#include <fstream>

using namespace std;

const int INTEGER_MIN = -2147483647, INTEGER_MAX = 2147483646;
const float FLOAT_MIN = -2000000, FLOAT_MAX = 2000000;

class CSVGenerator
{
private:
    // диапазон генерируемых символов строки
    char minChar = '!', maxChar = '~';
    // минимальная длина строки
    const int MIN_LEN = 1;
    // максимальная длина строки, кол-во колонок и строк
    int maxLen = 1, columns, rows;
    // неверный ли ввод
    bool cursedData = true;

    // допустимые типы данных в колонках таблицы
    vector<string> dataType = { "String", "Date", "Integer", "Float" };
    // типы данных для каждой колонки
    vector<string*> columnsTypes;
    // шапка таблицы
    string headers;


    // Генератор случайных символов
    char RandomCharGenerator();
    // Генератор случайных строк
    string RandomStringGenerator();
    // Генераторы случайных int
    int RandomIntegerGenerator(int minValue, int maxValue);
    int RandomIntegerGenerator();
    // Генератор случайной даты
    string RandomDateGenerator();
    // Генератор случайного float
    float RandomFloatGenerator();

    // Проверка на int (для проверки вводимых данных)
    bool IsStringInteger(const string& stringToCheck, int& number);
    // Генератор шапки таблицы
    void HeadersGenerator();
    // Генератор ячеек таблицы
    string CellGenerator(int currentColumn);
public:
    CSVGenerator(const string& col, const string& row, const string& len);
    // Сохранение результата в файл
    void SaveResultToFile(const string& filename);
};

