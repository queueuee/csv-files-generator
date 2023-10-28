#include "CSVGenerator.h"

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string outputFileName;
    string cols;
    string rows;
    string maxLength;
    string enc;

    for (int i = 1; i < argc; i+=2) 
    {
        string option = argv[i];

        if (option == "-col" && i + 1 < argc)
            cols = argv[i + 1];
        else if (option == "-row" && i + 1 < argc)
            rows = argv[i + 1];
        else if (option == "-len" && i + 1 < argc)
            maxLength = argv[i + 1];
        else if (option == "-enc" && i + 1 < argc)
            enc = argv[i + 1];
        else if (option == "-out" && i + 1 < argc)
            outputFileName = argv[i + 1];
        else
        {
            cerr << "Ошибка. Некорректный параметр " << option;
            return 1;
        }
    }

	CSVGenerator gen_csv(cols, rows, maxLength);
	gen_csv.SaveResultToFile(outputFileName);
}