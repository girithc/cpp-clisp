#include "stmt.cpp"
#include <list>
#include <iterator>
#include <string>
#include <iostream>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class lispInterpreter;
class lispFunction;
class lispFunctionReturn;
class lispEnvironment
{
    public:
        lispEnvironment();
        lispEnvironment(lispEnvironment* e);
        void define(string variable, list<string> variableValue);
        void defineLispFunction(string function, lispFunction* functionValue);
        list<string> getVariableValue(Token variable);
        lispFunction* getLispFunction(string functionName);
        void print(); 
        
    private:
        lispEnvironment* enclosing;
        unordered_map <string,list<string>> lispMap;
        unordered_map <string, lispFunction*> lispFunctionMap;   
            
};
class lispFunction
{
    public:
        Function* init;
        lispFunction(Function* init, lispEnvironment* lispFunctionEnvironment);
        list<string> lispFunctionCall(lispInterpreter* lispInterpreter,list<list<string>> lispFunctionArguments);
    
    private:
        list<string> lispFunctionReturnValue;
        lispEnvironment* lispFunctionEnvironment;

};
class lispInterpreter: public Visitor, VisitorStmt
{
    public:
        lispInterpreter(list<Stmt*> lispStmts);
        void interpret();
        void interpretLispStmt(Stmt* lispStmt);
        list<string> executeFunctionBlock(list<Stmt*> lispFunctionStmts, lispEnvironment* lispenv);

    private:
        lispEnvironment* lispenv;
        list<Stmt*> lispStmts;

        list<string> VisitCallExpr(Call* expr) override;
        list<string> VisitVariableExpr(Variable* expr) override;
        list<string> VisitLiteralExpr(Literal* expr) override;
        list<string> VisitConsExpr(Cons* expr) override;
        list<string> VisitCdrExpr(Cdr* expr) override;
        list<string> VisitCarExpr(Car* expr) override;

        list<string> VisitPrintStmt(Print* stmt) override;
        list<string> VisitVarStmt(Var* stmt) override;
        list<string> VisitFunctionStmt(Function* stmt) override;
        list<string> VisitExpressionStmt(Expression* stmt) override;
        list<string> VisitReturnStmt(Return* stmt) override;

        //helper
        list<string> eval(Expr* expr);
        list<string> cons(list<string> a, list<string> b);
        list<string> cdr(list<string> a);
        list<string> car(list<string> a);
};
class lispFunctionReturn
{
    public:
        Token token;
        list<string> lispFunctionReturnValue;
        lispFunctionReturn(list<string> value){lispFunctionReturnValue = value; }
        lispFunctionReturn(Token t, string message);
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
    cout << "   Enter define:" << variable << " = " << variableValue.front() << endl;
    lispMap.insert({{variable, variableValue}});

    //print();
}
void lispEnvironment::defineLispFunction(string function, lispFunction* functionValue)
{
    //define lispVariable
    cout << "   Enter defineLoxFunction:" << function << endl;
    list<string> functionVariableValue;
    functionVariableValue.push_back("<lispFunction>");
    define(function, functionVariableValue);

    //define lispFunction
    lispFunctionMap.insert({{function, functionValue}});
}
list<string> lispEnvironment::getVariableValue(Token variable)
{
    //print();
    cout << "   Entered getVariableValue" << endl;
    if(lispMap.find(variable.getTokenLexeme()) == lispMap.end())
    {
        string message;
        message.append("Variable \'");
        message.append(variable.getTokenLexeme());
        message.append("\' does not exist in the lisp environment.");
        throw invalid_argument(message);
    }
    else
    {
        cout << "found value of variable" << endl;
        //exit(1);
    }
    return lispMap[variable.getTokenLexeme()];
        
}
lispFunction* lispEnvironment::getLispFunction(string functionName)
{
    if(lispFunctionMap.find(functionName) != lispFunctionMap.end())
    {
        return lispFunctionMap[functionName];
    }

    string message;
    message.append("Lisp Function ");
    message.append(functionName);
    message.append(" does not exist in the lisp environment.");
    throw invalid_argument(message);
}
void lispEnvironment::print()
{
    cout << endl;
    for(auto it = lispMap.begin(); it != lispMap.end(); it++)
        cout << it->first << ", " << it->second.front() << endl;
    cout << endl;
}

//lispFunction
lispFunction::lispFunction(Function* init, lispEnvironment* lispFunctionEnvironment)
{
    this->init = init;
    this->lispFunctionEnvironment = lispFunctionEnvironment;
    //this->lispFunctionEnvironment->print();
}
list<string> lispFunction::lispFunctionCall(lispInterpreter* lispFunctionInterpreter, list<list<string>> lispFunctionArguments)
{
    //new lispFunction environment
    cout << "   Enter lispFunctionCall" << endl;
    lispEnvironment* lispenv = new lispEnvironment(lispFunctionEnvironment);
    list<Token>::iterator parametersIterator = init->params.begin();
    list<list<string>>::iterator parametersValueIterator = lispFunctionArguments.begin();

    for(int x = 0; x < init->params.size(); x++)
    {
        lispenv->define((*parametersIterator).getTokenLexeme(),(*parametersValueIterator));
        parametersIterator++;
        parametersValueIterator++;
    }
    try
    {
        cout << "       in lispFunctionCall" << endl;
        //lispenv->print();
        cout << "       ---" << endl;
        lispFunctionInterpreter->executeFunctionBlock(init->body, lispenv);
    }
    catch(lispFunctionReturn* lispFunctionReturnValue)
    {
        cout << "lispFunction Return value found." << endl;
    }
    
    return {""};
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
list<string> lispInterpreter::executeFunctionBlock(list<Stmt*> lispFunctionStmts, lispEnvironment* lispenv)
{
    list<string> result;
    cout << "       Enter executeFunctionBlock: " << lispFunctionStmts.size() << endl;
    //lispenv->print();
    this->lispenv = lispenv;
    for(auto it = lispFunctionStmts.begin(); it != lispFunctionStmts.end(); it++)
    {
        result =(*it)->Accept(this);
    }
    return {""};
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
list<string> lispInterpreter::VisitCallExpr(Call* expr)
{
    cout << "   Enter VisitCallExpr:" << expr->callee.getTokenLexeme()  << endl;
    string functionName = expr->callee.getTokenLexeme();
    lispFunction* function = lispenv->getLispFunction(functionName);

    list<list<string>> functionArguments;
    for(auto it = expr->arguments.begin(); it != expr->arguments.end(); it++)
        functionArguments.push_back(eval(*it));

    cout << "   Completed VisitCallExpr function arguments" << endl;
    return function->lispFunctionCall(this,functionArguments);
    //return {""};
}
list<string> lispInterpreter::VisitVariableExpr(Variable* expr) 
{
    cout << "Entered VisitVariableExpr: " << expr->name.getTokenLexeme() << endl;
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
    cout << "   Enter VisitPrintStmt --" << endl;

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
list<string> lispInterpreter::VisitFunctionStmt(Function* stmt)
{
    cout << "Enter VisitFunctionStmt" << endl;

    lispFunction* function = new lispFunction(stmt,lispenv);
    lispenv->defineLispFunction(stmt->name.getTokenLexeme(), function);

    return {""};
}
list<string> lispInterpreter::VisitExpressionStmt(Expression* stmt)
{
   list<string> functionResult = eval(stmt->expression);
   return functionResult;
}
list<string> lispInterpreter::VisitReturnStmt(Return* stmt)
{
    if(stmt) 
        throw new lispFunctionReturn(eval(stmt->value));

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