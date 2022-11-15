#include "stmt.cpp"
#include <list>
#include <iterator>
#include <string>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <vector>

using namespace std;

class lispInterpreter;
class lispFunction;
class lispFunctionReturn;
class lispEnvironment
{
    public:
        lispEnvironment();
        lispEnvironment(lispEnvironment* e);
        void define(string variable, vector<struct lispVar> variableValue);
        void defineLispFunction(string function, lispFunction* functionValue);
        vector<struct lispVar> getVariableValue(Token variable);
        lispFunction* getLispFunction(string functionName);
        void print(); 
        
    private:
        lispEnvironment* enclosing;
        unordered_map <string,vector<struct lispVar>> lispMap;
        unordered_map <string, lispFunction*> lispFunctionMap;   
            
};
class lispFunction
{
    public:
        Function* init;
        lispFunction(Function* init, lispEnvironment* lispFunctionEnvironment);
        vector<struct lispVar> lispFunctionCall(lispInterpreter* lispInterpreter,list<vector<struct lispVar>> lispFunctionArguments);
    
    private:
        vector<struct lispVar> lispFunctionReturnValue;
        lispEnvironment* lispFunctionEnvironment;

};
class lispInterpreter: public Visitor, VisitorStmt
{
    public:
        lispInterpreter(list<Stmt*> lispStmts);
        void interpret();
        void interpretLispStmt(Stmt* lispStmt);
        vector<struct lispVar> executeFunctionBlock(list<Stmt*> lispFunctionStmts, lispEnvironment* lispenv);

    private:
        lispEnvironment* lispenv;
        list<Stmt*> lispStmts;

        vector<struct lispVar> VisitCallExpr(Call* expr) override;
        vector<struct lispVar> VisitVariableExpr(Variable* expr) override;
        vector<struct lispVar> VisitLiteralExpr(Literal* expr) override;
        vector<struct lispVar> VisitConsExpr(Cons* expr) override;
        vector<struct lispVar> VisitCdrExpr(Cdr* expr) override;
        vector<struct lispVar> VisitCarExpr(Car* expr) override;

        vector<struct lispVar> VisitPrintStmt(Print* stmt) override;
        vector<struct lispVar> VisitVarStmt(Var* stmt) override;
        vector<struct lispVar> VisitFunctionStmt(Function* stmt) override;
        vector<struct lispVar> VisitExpressionStmt(Expression* stmt) override;
        vector<struct lispVar> VisitReturnStmt(Return* stmt) override;

        //helper
        vector<struct lispVar> eval(Expr* expr);
        vector<struct lispVar> cons(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> cdr(vector<struct lispVar> a);
        vector<struct lispVar> car(vector<struct lispVar> a);
};
class lispFunctionReturn
{
    public:
        Token token;
        vector<struct lispVar> lispFunctionReturnValue;
        lispFunctionReturn(vector<struct lispVar> value){lispFunctionReturnValue = value; }
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
void lispEnvironment::define(string variable, vector<struct lispVar> variableValue)
{
    cout << "   Enter define:" << variable << " = " << variableValue.front().value << endl;
    lispMap.insert({{variable, variableValue}});

    //print();
}
void lispEnvironment::defineLispFunction(string function, lispFunction* functionValue)
{
    //define lispVariable
    cout << "   Enter defineLoxFunction:" << function << endl;
    vector<struct lispVar> functionVariableValue;
    struct lispVar lv;
    lv.value = "<lispFunction>";
    functionVariableValue.push_back(lv);
    define(function, functionVariableValue);

    //define lispFunction
    lispFunctionMap.insert({{function, functionValue}});
}
vector<struct lispVar> lispEnvironment::getVariableValue(Token variable)
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
        cout << it->first << ", " << it->second.front().value << endl;
    cout << endl;
}

//lispFunction
lispFunction::lispFunction(Function* init, lispEnvironment* lispFunctionEnvironment)
{
    this->init = init;
    this->lispFunctionEnvironment = lispFunctionEnvironment;
    //this->lispFunctionEnvironment->print();
}
vector<struct lispVar> lispFunction::lispFunctionCall(lispInterpreter* lispFunctionInterpreter, list<vector<struct lispVar>> lispFunctionArguments)
{
    //new lispFunction environment
    cout << "   Enter lispFunctionCall" << endl;
    lispEnvironment* lispenv = new lispEnvironment(lispFunctionEnvironment);
    list<Token>::iterator parametersIterator = init->params.begin();
    list<vector<struct lispVar>>::iterator parametersValueIterator = lispFunctionArguments.begin();

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
        return lispFunctionReturnValue->lispFunctionReturnValue;
    }
    
    
    vector<struct lispVar> placeholder;
    return placeholder;
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
    vector<struct lispVar> returnplaceholder = lispStmt->Accept(this);
}
vector<struct lispVar> lispInterpreter::executeFunctionBlock(list<Stmt*> lispFunctionStmts, lispEnvironment* lispenv)
{
    vector<struct lispVar> result;
    cout << "       Enter executeFunctionBlock: " << lispFunctionStmts.size() << endl;
    //lispenv->print();
    this->lispenv = lispenv;
    for(auto it = lispFunctionStmts.begin(); it != lispFunctionStmts.end(); it++)
    {
        result =(*it)->Accept(this);
    }
    
    vector<struct lispVar> placeholder;
    return placeholder;
}

//lispExpr
vector<struct lispVar> lispInterpreter::VisitConsExpr(Cons* expr)
{
    cout << "Entered VisitConsExpr" << endl;
    vector<struct lispVar> a = eval(expr->a);
    vector<struct lispVar> b = eval(expr->b);
    
    return cons(a,b);
    //return {""};
}
vector<struct lispVar> lispInterpreter::VisitCdrExpr(Cdr* expr)
{
    cout << "Entered VisitCdrExpr" << endl;
    vector<struct lispVar> a = eval(expr->a);

    return cdr(a);
}
vector<struct lispVar> lispInterpreter::VisitCarExpr(Car* expr)
{
    cout << "Entered VisitCarExpr" << endl;
    vector<struct lispVar> a = eval(expr->a);
    
    return car(a);
}
vector<struct lispVar> lispInterpreter::VisitCallExpr(Call* expr)
{
    cout << "   Enter VisitCallExpr:" << expr->callee.getTokenLexeme()  << endl;
    string functionName = expr->callee.getTokenLexeme();
    lispFunction* function = lispenv->getLispFunction(functionName);

    list<vector<struct lispVar>> functionArguments;
    for(auto it = expr->arguments.begin(); it != expr->arguments.end(); it++)
        functionArguments.push_back(eval(*it));

    cout << "   Completed VisitCallExpr function arguments" << endl;
    return function->lispFunctionCall(this,functionArguments);
    //return {""};
}
vector<struct lispVar> lispInterpreter::VisitVariableExpr(Variable* expr) 
{
    cout << "Entered VisitVariableExpr: " << expr->name.getTokenLexeme() << endl;
    return lispenv->getVariableValue(expr->name);
}
vector<struct lispVar> lispInterpreter::VisitLiteralExpr(Literal* expr) 
{
    cout << "Entered VisitLiteralExpr: " << endl;
    
    return expr->literalValue;
}

//lispStmt
vector<struct lispVar> lispInterpreter::VisitPrintStmt(Print* stmt)
{
    cout << "   Enter VisitPrintStmt --" << endl;

    vector<struct lispVar> value = eval(stmt->expression);

    cout << "lisp>" ;
    for(auto iterator = value.begin(); iterator != value.end(); iterator++)
        cout << "(" << (*iterator).value << ")";
    cout << endl;


    vector<struct lispVar> placeholder;
    return placeholder;
}
vector<struct lispVar> lispInterpreter::VisitVarStmt(Var* stmt)
{
    cout << "   Enter VisitVarStmt" << endl;

    vector<struct lispVar> variableValue;
    if(stmt->init) variableValue = eval(stmt->init);

    cout << "   completed eval in VisitVarStmt" << endl;

    lispenv->define(stmt->name.getTokenLexeme(), variableValue);
    
    
    vector<struct lispVar> placeholder;
    return placeholder;
}
vector<struct lispVar> lispInterpreter::VisitFunctionStmt(Function* stmt)
{
    cout << "Enter VisitFunctionStmt" << endl;

    lispFunction* function = new lispFunction(stmt,lispenv);
    lispenv->defineLispFunction(stmt->name.getTokenLexeme(), function);

    
    vector<struct lispVar> placeholder;
    return placeholder;
}
vector<struct lispVar> lispInterpreter::VisitExpressionStmt(Expression* stmt)
{
   vector<struct lispVar> functionResult = eval(stmt->expression);
   return functionResult;
}
vector<struct lispVar> lispInterpreter::VisitReturnStmt(Return* stmt)
{
    if(stmt) 
        throw new lispFunctionReturn(eval(stmt->value));

    
    vector<struct lispVar> placeholder;
    return placeholder;
}

//helper
vector<struct lispVar> lispInterpreter::eval(Expr* expr)
{
    return expr->Accept(this);
}
vector<struct lispVar> lispInterpreter::cons(vector<struct lispVar> a, vector<struct lispVar> b)
{
    for(auto iterator = b.begin(); iterator != b.end(); iterator++)
    {
        a.push_back(*iterator);
    }
    return a;
}
vector<struct lispVar> lispInterpreter::cdr(vector<struct lispVar> a)
{
    a.erase(a.begin());
    return a;
}
vector<struct lispVar> lispInterpreter::car(vector<struct lispVar> a)
{
    vector<struct lispVar> aprime; 
    aprime.push_back(a.front());
    return aprime;
}