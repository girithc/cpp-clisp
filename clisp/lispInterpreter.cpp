#include "stmt.cpp"
#include <list>
#include <iterator>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

class lispInterpreter;
class lispEnvironment
{
    public:
        lispEnvironment();
        lispEnvironment(lispEnvironment* e);
        
    private:
        lispEnvironment* enclosing;
        unordered_map <string,list<string>> lispVariables;
};

class lispInterpreter: public Visitor, VisitorStmt
{
    public:
        lispInterpreter(list<Stmt*> lispStmts);
        void interpret();
        void interpretLispStmt(Stmt* lispStmt);

        
    
    private:
        list<Stmt*> lispStmts;

        string VisitVariableExpr(Variable* expr) override;
        string VisitLiteralExpr(Literal* expr) override;

        string VisitPrintStmt(Print* stmt) override;
        string VisitVarStmt(Var* stmt) override;
        
        //helper
        string eval(Expr* expr);

};

lispEnvironment::lispEnvironment()
{
    enclosing = NULL;
}
lispEnvironment::lispEnvironment(lispEnvironment* e)
{
    enclosing = e;
}

lispInterpreter::lispInterpreter(list<Stmt*> lispStmts)
{
    this->lispStmts = lispStmts;
}

void
lispInterpreter::interpret()
{
    try {
        cout << endl << "Enter interpret" << endl << endl;
        list<Stmt*>::iterator lispStmtsIterator;
        int lispStmtCounter = 0;

        for(lispStmtsIterator = lispStmts.begin(); lispStmtsIterator != lispStmts.end(); lispStmtsIterator++)
        {   
            lispStmtCounter++;
            cout << "   interpret LispStmt:" << lispStmtCounter << endl;
            interpretLispStmt(*lispStmtsIterator);
        }

    } catch(...) {
        cout << "Error found in Interpreter" << endl;
    }
}

void
lispInterpreter::interpretLispStmt(Stmt* lispStmt)
{
    cout << "   Enter interpretLispStmt" << endl;
    string returnplaceholder = lispStmt->Accept(this);
}

string lispInterpreter::VisitVariableExpr(Variable* expr) 
{
    cout << "Entered VisitVariableExpr: " << endl;
    return "";
}
string lispInterpreter::VisitLiteralExpr(Literal* expr) 
{
    cout << "Entered VisitLiteralExpr: " << endl;
    return expr->value;
}

string
lispInterpreter::VisitPrintStmt(Print* stmt)
{
    cout << "   Enter VisitPrintStmt" << endl;

    string value = eval(stmt->expression);
    cout << "lisp>" << value << endl;

    return "";
}

string 
lispInterpreter::VisitVarStmt(Var* stmt)
{
    cout << "   Enter VisitVarStmt" << endl;
    return "";
}

string
lispInterpreter::eval(Expr* expr)
{
    return expr->Accept(this);
}