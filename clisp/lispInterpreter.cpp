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
        void define(string variable, list<string> variableValue);
        list<string> getVariableValue(Token variable);
        
    private:
        lispEnvironment* enclosing;
        unordered_map <string,list<string>> lispMap;

        
};
class lispInterpreter: public Visitor, VisitorStmt
{
    public:
        lispInterpreter(list<Stmt*> lispStmts);
        void interpret();
        void interpretLispStmt(Stmt* lispStmt);

    private:
        lispEnvironment* lispenv;
        list<Stmt*> lispStmts;

        list<string> VisitVariableExpr(Variable* expr) override;
        list<string> VisitLiteralExpr(Literal* expr) override;
        list<string> VisitConsExpr(Cons* expr) override;
        list<string> VisitCdrExpr(Cdr* expr) override;
        list<string> VisitCarExpr(Car* expr) override;

        list<string> VisitPrintStmt(Print* stmt) override;
        list<string> VisitVarStmt(Var* stmt) override;
        
        //helper
        list<string> eval(Expr* expr);
        list<string> cons(list<string> a, list<string> b);
        list<string> cdr(list<string> a);
        list<string> car(list<string> a);
};

//lispEnvironment
lispEnvironment::lispEnvironment()
{
    enclosing = NULL;
}
lispEnvironment::lispEnvironment(lispEnvironment* e)
{
    enclosing = e;
}
void lispEnvironment::define(string variable, list<string> variableValue)
{
    cout << "   Enter define:" << variableValue.front() << endl;
    lispMap.insert({{variable, variableValue}});
}
list<string> lispEnvironment::getVariableValue(Token variable)
{
    if(lispMap.find(variable.getTokenLexeme()) == lispMap.end())
    {
        string message;
        message.append("Variable \'");
        message.append(variable.getTokenLexeme());
        message.append("\' does not exist in the lisp environment.");
        throw invalid_argument(message);
    }
    return lispMap[variable.getTokenLexeme()];
        
}

//lispInterpreter
lispInterpreter::lispInterpreter(list<Stmt*> lispStmts)
{
    this->lispStmts = lispStmts;
    lispenv = new lispEnvironment();
}
void lispInterpreter::interpret()
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
void lispInterpreter::interpretLispStmt(Stmt* lispStmt)
{
    cout << "   Enter interpretLispStmt" << endl;
    list<string> returnplaceholder = lispStmt->Accept(this);
}

//lispExpr
list<string> lispInterpreter::VisitConsExpr(Cons* expr)
{
    cout << "Entered VisitConsExpr" << endl;
    list<string> a = eval(expr->a);
    list<string> b = eval(expr->b);
    
    return cons(a,b);
    //return {""};
}
list<string> lispInterpreter::VisitCdrExpr(Cdr* expr)
{
    cout << "Entered VisitCdrExpr" << endl;
    list<string> a = eval(expr->a);

    return cdr(a);
}
list<string> lispInterpreter::VisitCarExpr(Car* expr)
{
    cout << "Entered VisitCarExpr" << endl;
    list<string> a = eval(expr->a);
    
    return car(a);
}
list<string> lispInterpreter::VisitVariableExpr(Variable* expr) 
{
    cout << "Entered VisitVariableExpr: " << endl;
    return lispenv->getVariableValue(expr->name);
}
list<string> lispInterpreter::VisitLiteralExpr(Literal* expr) 
{
    cout << "Entered VisitLiteralExpr: " << endl;
    return expr->value;
}

//lispStmt
list<string> lispInterpreter::VisitPrintStmt(Print* stmt)
{
    cout << "   Enter VisitPrintStmt" << endl;

    list<string> value = eval(stmt->expression);

    cout << "lisp>" ;
    for(auto iterator = value.begin(); iterator != value.end(); iterator++)
        cout << "(" << (*iterator) << ")";
    cout << endl;

    return {""};
}
list<string> lispInterpreter::VisitVarStmt(Var* stmt)
{
    cout << "   Enter VisitVarStmt" << endl;

    list<string> variableValue;
    if(stmt->init) variableValue = eval(stmt->init);

    cout << "   completed eval in VisitVarStmt" << endl;

    lispenv->define(stmt->name.getTokenLexeme(), variableValue);
    return {""};
}

//helper
list<string> lispInterpreter::eval(Expr* expr)
{
    return expr->Accept(this);
}
list<string> lispInterpreter::cons(list<string> a, list<string> b)
{
    for(auto iterator = b.begin(); iterator != b.end(); iterator++)
    {
        a.push_back(*iterator);
    }
    return a;
}
list<string> lispInterpreter::cdr(list<string> a)
{
    a.pop_front();
    return a;
}
list<string> lispInterpreter::car(list<string> a)
{
    list<string> aprime; 
    aprime.push_back(a.front());
    return aprime;
}