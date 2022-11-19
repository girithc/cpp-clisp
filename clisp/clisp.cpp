#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include "testLispInterpreter.cpp"

class Lisp
{
    public:
        void runFile(std::string lispFile);
    private:
        void run(std::string lispCode);
};

void Lisp::runFile(std::string lispFile)
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
void Lisp::run(std::string lispCode)
{
    //cout << "LispCode in Main: " << endl << lispCode << endl;
    LispScanner* scanner = new LispScanner(lispCode);
    list<Token> lispTokens = scanner->scanTokens();

    //for(auto itr = lispTokens.begin(); itr != lispTokens.end(); itr++)
    //{
        //cout << itr->getTokenType() << endl;
    //}

    //cout << endl << "---- Start Parser ----" << endl;
    lispParser parser(lispTokens);
    list<Stmt*> lispStmts = parser.parse();
    //cout << "---- Parser completed ----" << endl << endl;

    //cout << endl << "---- Start Interpreter ----" << endl;
    lispInterpreter* interpreter = new lispInterpreter(lispStmts);
    interpreter->interpret();
    //cout << "---- Interpreter completed ----" << endl << endl;
}

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        std::cout << "User input is missing the file name" << std::endl;
    }
    else if(argc == 2 && (strcmp(argv[1],"test") == 0))
    {
        cout << "Start testing lisp Interpreter..." << endl;
        testLispInterpreter();
        cout << "Finished testing lisp Interpreter." << endl;
    }
    else
    {
        Lisp lsp;
        lsp.runFile(argv[1]);
    }
}