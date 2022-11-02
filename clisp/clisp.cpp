#include <iostream>
#include <string>
#include <fstream>
#include "scanner.cpp"

void runFile(std::string file)
{
    std::ifstream fPtr;
    fPtr.open(file);

    std::string fileCode;
    std::string fileLine;
    std::string fileNewLine = "\n";

    if(fPtr.good())
    {
        while(!fPtr.eof())
        {
            std::getline(fPtr, fileLine);
            fileCode.append(fileLine);
            fileCode.append(fileNewLine);
        }

        run(fileCode);
    }
}

void run(std::string code)
{
    LispScanner* scanner = new LispScanner(code);
}


int main(int argc, char** argv)
{
    if(argc == 1)
    {
        std::cout << "User input is missing the file name" << std::endl;
    }
    else if(argc == 2)
    {
        runFile(argv[1]);
    }
}