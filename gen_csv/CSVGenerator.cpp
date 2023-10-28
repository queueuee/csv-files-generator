#include "CSVGenerator.h"

bool CSVGenerator::IsStringInteger(const string& stringToCheck, int& number)
{
    try
    {
        size_t pos;
        number = stoi(stringToCheck, &pos);

        if (pos != stringToCheck.length())
        {
            cerr << "Некорректный формат integer. ";
            return false;
        }
    }
    catch (const invalid_argument& e)
    {
        cerr << "Некорректный формат integer. ";
        return false;
    }
    catch (const out_of_range& e)
    {
        cerr << "Слишком большое число integer. ";
        return false;
    }

    if (number > 0)
        return true;
    else
        return false;
}
char CSVGenerator::RandomCharGenerator()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(minChar, maxChar);
    return static_cast<char>(distribution(gen));
}
int CSVGenerator::RandomIntegerGenerator(int minValue, int maxValue)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(minValue, maxValue);
    return distribution(gen);
}
int CSVGenerator::RandomIntegerGenerator()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(INTEGER_MIN, INTEGER_MAX);
    return distribution(gen);
}

string CSVGenerator::RandomStringGenerator()
{
    string randomString;
    int length = RandomIntegerGenerator(MIN_LEN, maxLen);
    char quotes = '\"';
    bool rezervSymb = false;

    for (int i = 0; i < length; i++)
    {
        char randomChar = RandomCharGenerator();
        
        while (randomChar == '\\')
            randomChar = RandomCharGenerator();
        
        if (randomChar == quotes)
        {
            randomString += quotes;
            rezervSymb = true;
            length++;
        }
        else if (randomChar == ';')
            rezervSymb = true;

        randomString += randomChar;
    }

    if (rezervSymb)
    {
        randomString.insert(randomString.begin(), '\"');
        randomString.insert(randomString.end(), '\"');
    }

    return randomString;
}
string CSVGenerator::RandomDateGenerator()
{
    int day = RandomIntegerGenerator(1, 31);
    int month = RandomIntegerGenerator(1, 12);
    int year = RandomIntegerGenerator(100, 2999);

    string dayString = (day < 10) ? "0" + to_string(day) : to_string(day);
    string monthString = (month < 10) ? "0" + to_string(month) : to_string(month);
    string yearString = (year < 1000) ? "0" + to_string(year) : to_string(year);

    return dayString + '.' + monthString + '.' + yearString;
}

float CSVGenerator::RandomFloatGenerator()
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> distribution(FLOAT_MIN, FLOAT_MAX);
    return distribution(gen);
}

void CSVGenerator::HeadersGenerator()
{
    if (!headers.empty())
    {
        headers.clear();
        columnsTypes.clear();
    }

    int randomType = RandomIntegerGenerator(0, dataType.size() - 1);
    headers += RandomStringGenerator();
    columnsTypes.push_back(&dataType[randomType]);
    headers += ' ' + *columnsTypes[0];

    for (int i = 1; i < columns; i++)
    {
        headers += ';';
        headers += RandomStringGenerator();
        randomType = RandomIntegerGenerator(0, dataType.size() - 1);
        columnsTypes.push_back(&dataType[randomType]);
        headers += ' ' + *columnsTypes[i];
    }
    headers += "\n";
}
string CSVGenerator::CellGenerator(int currentColumn)
{
    if (*columnsTypes[currentColumn] == "String")
        return RandomStringGenerator();
    if (*columnsTypes[currentColumn] == "Date")
        return RandomDateGenerator();
    if (*columnsTypes[currentColumn] == "Integer")
        return to_string(RandomIntegerGenerator());
    if (*columnsTypes[currentColumn] == "Float")
        return to_string(RandomFloatGenerator());
}
CSVGenerator::CSVGenerator(const string& col, const string& row, const string& len)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    if (!IsStringInteger(col, columns))
    {
        cerr << "Ошибка ввода. Некорректное значение -col";
        return;
    }
    else if (!IsStringInteger(row, rows))
    {
        cerr << "Ошибка ввода. Некорректное значение -row";
        return;
    }
    else if (!IsStringInteger(len, maxLen))
    {
        cerr << "Ошибка ввода. Некорректное значение -len";
        return;
    }

    cursedData = false;
}
void CSVGenerator::SaveResultToFile(const string& filename)
{
    if (cursedData == true)
        return;

    ofstream outFile(filename);

    HeadersGenerator();
    outFile << headers;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            outFile << CellGenerator(j) << ';';
        }
        outFile << "\n";
    }

    cout << "Успех";
    outFile.close();
}