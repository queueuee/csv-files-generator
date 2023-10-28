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
    // �������� ������������ �������� ������
    char minChar = '!', maxChar = '~';
    // ����������� ����� ������
    const int MIN_LEN = 1;
    // ������������ ����� ������, ���-�� ������� � �����
    int maxLen = 1, columns, rows;
    // �������� �� ����
    bool cursedData = true;

    // ���������� ���� ������ � �������� �������
    vector<string> dataType = { "String", "Date", "Integer", "Float" };
    // ���� ������ ��� ������ �������
    vector<string*> columnsTypes;
    // ����� �������
    string headers;


    // ��������� ��������� ��������
    char RandomCharGenerator();
    // ��������� ��������� �����
    string RandomStringGenerator();
    // ���������� ��������� int
    int RandomIntegerGenerator(int minValue, int maxValue);
    int RandomIntegerGenerator();
    // ��������� ��������� ����
    string RandomDateGenerator();
    // ��������� ���������� float
    float RandomFloatGenerator();

    // �������� �� int (��� �������� �������� ������)
    bool IsStringInteger(const string& stringToCheck, int& number);
    // ��������� ����� �������
    void HeadersGenerator();
    // ��������� ����� �������
    string CellGenerator(int currentColumn);
public:
    CSVGenerator(const string& col, const string& row, const string& len);
    // ���������� ���������� � ����
    void SaveResultToFile(const string& filename);
};

