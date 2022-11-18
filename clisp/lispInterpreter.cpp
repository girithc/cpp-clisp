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
        unordered_map <string,vector<struct lispVar>> lispMap;
        unordered_map <string, lispFunction*> lispFunctionMap;   
        
    private:
        lispEnvironment* enclosing;
        
            
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

        vector<struct lispVar> VisitBinaryExpr(Binary* expr) override;
        vector<struct lispVar> VisitCallExpr(Call* expr) override;
        vector<struct lispVar> VisitVariableExpr(Variable* expr) override;
        vector<struct lispVar> VisitLiteralExpr(Literal* expr) override;
        vector<struct lispVar> VisitConsExpr(Cons* expr) override;
        vector<struct lispVar> VisitCdrExpr(Cdr* expr) override;
        vector<struct lispVar> VisitCarExpr(Car* expr) override;
        vector<struct lispVar> VisitYesOrNoExpr(YesOrNo* expr) override;

        vector<struct lispVar> VisitPrintStmt(Print* stmt) override;
        vector<struct lispVar> VisitVarStmt(Var* stmt) override;
        vector<struct lispVar> VisitFunctionStmt(Function* stmt) override;
        vector<struct lispVar> VisitExpressionStmt(Expression* stmt) override;
        vector<struct lispVar> VisitReturnStmt(Return* stmt) override;
        vector<struct lispVar> VisitCondStmt(Cond* stmt) override;

        //helper
        vector<struct lispVar> eval(Expr* expr);
        vector<struct lispVar> cons(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> cdr(vector<struct lispVar> a);
        vector<struct lispVar> car(vector<struct lispVar> a);
        vector<struct lispVar> add(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> minus(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> multiply(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> divide(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> equal(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> not_equal(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> greater(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> greater_equal(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> less(vector<struct lispVar> a, vector<struct lispVar> b);
        vector<struct lispVar> less_equal(vector<struct lispVar> a, vector<struct lispVar> b);
        string compare(string a, string b, string binaryoperator);
        string compareString(string a, string b, string binaryoperator);
        string compareNumber(string a, string b, string binaryoperator);
        bool isNumber(string a, string b);
        bool isNumber(string a);
        bool isString(string a);
        bool isNil(string a);
        bool isList(vector<struct lispVar> a);
        void print(vector<struct lispVar> a);
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
    print();
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
    cout << "   Entered getVariableValue: " << variable.getTokenLexeme() << endl;
    print();
    if(lispMap.find(variable.getTokenLexeme()) == lispMap.end())
    {
        if(enclosing)
        {
            cout << "   entering enclosing" << endl;
            return enclosing->getVariableValue(variable);
        }
    }
    else
    {
        cout << "found value of variable" << endl;
        return lispMap[variable.getTokenLexeme()];
        //exit(1);
    }
    
    string message;
    message.append("Variable \'");
    message.append(variable.getTokenLexeme());
    message.append("\' does not exist in the lisp environment.");
    throw invalid_argument(message);
        
}
lispFunction* lispEnvironment::getLispFunction(string functionName)
{
    cout << "   Entered getLispFunction" << endl;
    print();
    if(lispFunctionMap.find(functionName) == lispFunctionMap.end())
    {
        cout << "   entering enclosing" << endl;
        return enclosing->getLispFunction(functionName);
    }
    else
    {
        cout << "found value of Function" << endl;
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
    cout << "   Declare lispFunction()" << endl;
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
vector<struct lispVar> lispInterpreter::VisitBinaryExpr(Binary* expr)
{
    cout << "   Enter VisitBinaryExpr" << endl;

    vector<struct lispVar> a = eval(expr->left);
    vector<struct lispVar> b = eval(expr->right);

    // result any number in the form of a string
    if(expr->op.getTokenType() == "PLUS") return add(a,b);
    else if(expr->op.getTokenType() == "MINUS") return minus(a,b);
    else if(expr->op.getTokenType() == "STAR") return multiply(a,b);
    else if(expr->op.getTokenType() == "SLASH") return divide(a,b);

    // result true or false
    else if(expr->op.getTokenType() == "EQUAL") return equal(a,b);
    else if(expr->op.getTokenType() == "BANG_EQUAL") return not_equal(a,b);
    else if(expr->op.getTokenType() == "GREATER") return greater(a,b);
    else if(expr->op.getTokenType() == "GREATER_EQUAL") return greater_equal(a,b);
    else if(expr->op.getTokenType() == "LESS") return less(a,b);
    else if(expr->op.getTokenType() == "LESS_EQUAL") return less_equal(a,b);

    vector<struct lispVar> lv;
    return lv;
}
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
    cout << "       function name:" << function->init->name.getTokenLexeme() << endl; 
    cout << "       args size:" << expr->arguments.size() << endl;

    list<vector<struct lispVar>> functionArguments;
    for(auto it = expr->arguments.begin(); it != expr->arguments.end(); it++)
    {
        cout << "       function arguments" << endl;
        functionArguments.push_back(eval(*it));
    }
        

    cout << "   Completed VisitCallExpr function arguments" << endl;
    lispEnvironment* tempenv = new lispEnvironment();
    tempenv->lispFunctionMap = lispenv->lispFunctionMap;
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
vector<struct lispVar> lispInterpreter::VisitYesOrNoExpr(YesOrNo* expr)
{
    cout << "Entered VisitYesOrNoExpr: " << endl;
    vector<struct lispVar> a = eval(expr->value);

    struct lispVar lv;
    if(expr->name.getTokenType() == enum_str[ISNUMBER])
        lv.value = isNumber(a.front().value, a.front().value) ? "true" : "false";
    
    else if(expr->name.getTokenType() == enum_str[ISNIL])
        lv.value = isNil(a.front().value) ? "true" : "false";

    else if(expr->name.getTokenType() == enum_str[ISSYMBOL])
        lv.value = isNumber(a.front().value, a.front().value) ? "false" : "true";

    else if(expr->name.getTokenType() == enum_str[ISLIST])
        lv.value = isList(a) ? "true" : "false";

    vector<struct lispVar> returnbool;
    returnbool.push_back(lv);

    return returnbool;
}

//lispStmt
vector<struct lispVar> lispInterpreter::VisitPrintStmt(Print* stmt)
{
    cout << "   Enter VisitPrintStmt --" << endl;

    vector<struct lispVar> value = eval(stmt->expression);

    cout << "lisp>" ;
    cout << "[";
    print(value);
    cout << "]";
    //for(auto iterator = value.begin(); iterator != value.end(); iterator++)
    //    cout << "(" << (*iterator).value << ")";
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
    cout << "   Enter VisitExpressionStmt" << endl;
    vector<struct lispVar> functionResult = eval(stmt->expression);
    return functionResult;
}
vector<struct lispVar> lispInterpreter::VisitReturnStmt(Return* stmt)
{
    cout << "   Enter VisitReturnStmt" << endl;
    if(stmt)
    {   
        cout << "       in return" << endl;
        throw new lispFunctionReturn(eval(stmt->value));
    } 

    vector<struct lispVar> placeholder;
    return placeholder;
}
vector<struct lispVar> lispInterpreter::VisitCondStmt(Cond* stmt)
{
    cout << "   Enter VisitCondStmt" << endl;
    auto it_branch = stmt->conditionbranches.begin();
    for(auto it = stmt->conditions.begin(); it != stmt->conditions.end(); it++)
    {
        if(eval(*it).front().value == "true")  return (*it_branch)->Accept(this);
        else it_branch++;

    }
    vector<struct lispVar> lv_;
    return lv_;
}

//helper
vector<struct lispVar> lispInterpreter::eval(Expr* expr)
{
    return expr->Accept(this);
}
vector<struct lispVar> lispInterpreter::cons(vector<struct lispVar> a, vector<struct lispVar> b)
{
    vector<struct lispVar> lv;
    
    if(a.size() == 1 && !a.front().value.empty())
    {
        struct lispVar x;
        x.value = a.front().value;
        lv.push_back(x);
    }
    else
    {
        struct lispVar x;
        x.next = a;
        lv.push_back(x);
    }

    if(b.size() == 1 && !b.front().value.empty())
    {
        struct lispVar x;
        x.value = b.front().value;
        lv.push_back(x);
    }
    else
    {
        struct lispVar x;
        x.next = b;
        lv.push_back(x);
    }

    return lv;
}
vector<struct lispVar> lispInterpreter::cdr(vector<struct lispVar> a)
{
    a.erase(a.begin());
    if(a.front().value.empty())
    {
        return a.front().next;            
    }
    return a;
}
vector<struct lispVar> lispInterpreter::car(vector<struct lispVar> a)
{
    vector<struct lispVar> aprime; 
    
    if(a.front().value.empty()) return a.front().next;
    
    else aprime.push_back(a.front());

    return aprime;
}
vector<struct lispVar> lispInterpreter::add(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = to_string(stod(a.front().value)+stod(b.front().value));

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
vector<struct lispVar> lispInterpreter::minus(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = to_string(stod(a.front().value)-stod(b.front().value));

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
vector<struct lispVar> lispInterpreter::multiply(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = to_string(stod(a.front().value)*stod(b.front().value));

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
vector<struct lispVar> lispInterpreter::divide(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = to_string(stod(a.front().value)/stod(b.front().value));

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
vector<struct lispVar> lispInterpreter::equal(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = compare(a.front().value, b.front().value, "=");

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
vector<struct lispVar> lispInterpreter::not_equal(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = compare(a.front().value, b.front().value, "!=");

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
vector<struct lispVar> lispInterpreter::less(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = compare(a.front().value, b.front().value, "<");

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
vector<struct lispVar> lispInterpreter::less_equal(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = compare(a.front().value, b.front().value, "<=");

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
vector<struct lispVar> lispInterpreter::greater(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = compare(a.front().value, b.front().value, ">");

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
vector<struct lispVar> lispInterpreter::greater_equal(vector<struct lispVar> a, vector<struct lispVar> b)
{
    struct lispVar lv;
    lv.value = compare(a.front().value, b.front().value, ">=");

    vector<struct lispVar> lv_;
    lv_.push_back(lv);
    return lv_;
}
string lispInterpreter::compare(string a, string b, string binaryoperator)
{
    if(isNumber(a,b)) return compareNumber(a, b, binaryoperator);
    else return compareString(a, b, binaryoperator);
}
string lispInterpreter::compareString(string a, string b, string binaryoperator)
{
    if (binaryoperator =="<")
    {   
        if((a) < (b)) return "true"; 
        return "false";
    }
    else if (binaryoperator == "<=")
    {   
        if((a) <= (b)) return "true"; 
        return "false";
    }
    else if (binaryoperator == ">")
    {   
        if((a) > (b)) return "true"; 
        return "false";
    }
    else if (binaryoperator == ">=")
    {   
        if((a) >= (b)) return "true"; 
        return "false";
    }
    else if (binaryoperator == "!=")
    {   
        if((a) != (b))  return "true"; 
        return "false";
    }
    else if (binaryoperator == "=")
    {   
        if((a) == (b)) return "true"; 
        return "false";
    }
    
    return "false";
}
string lispInterpreter::compareNumber(string a, string b, string binaryoperator)
{
    if (binaryoperator =="<")
    {   
        if(stod(a) < stod(b)) return "true"; 
        return "false";
    }
    else if (binaryoperator == "<=")
    {   
        if(stod(a) <= stod(b)) return "true"; 
        return "false";
    }
    else if (binaryoperator == ">")
    {   
        if(stod(a) > stod(b)) return "true"; 
        return "false";
    }
    else if (binaryoperator == ">=")
    {   
        if(stod(a) >= stod(b)) return "true"; 
        return "false";
    }
    else if (binaryoperator == "!=")
    {   
        if(stod(a) != stod(b))  return "true"; 
        return "false";
    }
    else if (binaryoperator == "=")
    {   
        if(stod(a) == stod(b)) return "true"; 
        return "false";
    }
    
    return "false";
}
bool lispInterpreter::isNumber(string a, string b)
{
    for (int x = 0; x < a.length(); x++)
    {
        if (isdigit(a[x])) continue;
        else if(a[x] =='.' && isdigit(a[x+1])) continue;
        else return false;
    }
    for (int y = 0; y < b.length(); y++)
    {
        if (isdigit(b[y])) continue;
        else if(b[y] =='.' && isdigit(b[y+1])) continue;
        else return false;
    }

    return true;
}
bool lispInterpreter::isNil(string a)
{
    if(a == "") return true;

    return false;
}
bool lispInterpreter::isList(vector<struct lispVar> a)
{
    if(a.size() > 1) return true;
    return false;
}
void lispInterpreter::print(vector<struct lispVar> a)
{
    int counter = 0;
    for(auto it = a.begin(); it != a.end(); it++)
    {
        //cout << "(tc:" << counter+1 << ")" << endl;
        if((*it).value.empty())
        {
            cout << "(";
            print((*it).next);
            cout << ")";
        } 
        else cout << " (" << (*it).value << ") ";


        counter++;
    }
}