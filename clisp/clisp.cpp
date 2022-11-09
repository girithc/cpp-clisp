#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include "scanner.cpp"

class Lisp
{
    public:
        void runFile(std::string lispFile);
    private:
        void run(std::string lispCode);
};

void 
Lisp::runFile(std::string lispFile)
{
    std::ifstream fPtr;
    fPtr.open(lispFile);

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

void 
Lisp::run(std::string lispCode)
{
    cout << "LispCode in Main: " << endl << lispCode << endl;
    LispScanner* scanner = new LispScanner(lispCode);
    list<Token> lispTokens = scanner->scanTokens();

    for(auto itr = lispTokens.begin(); itr != lispTokens.end(); itr++)
    {
        cout << itr->getTokenType() << endl;
    }
    lispParser parser(lispTokens);
    cout << endl << "---- Start Parse ----" << endl;
    list<Stmt*> stmts = parser.parse();
    cout << "---- Parse ended ----" << endl << endl;
}


int main(int argc, char** argv)
{
    if(argc == 1)
    {
        std::cout << "User input is missing the file name" << std::endl;
    }
    else if(argc == 2)
    {
        Lisp lsp;
        lsp.runFile(argv[1]);
    }
}