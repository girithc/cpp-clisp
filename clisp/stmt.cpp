//refer appendix 2 to start
#include <list>
#include <string>
#include <iostream>
#include <vector>

#include "expr.cpp"

using namespace std;

class VisitorStmt;
class Stmt
{
    public:
        virtual ~Stmt(){};
        virtual vector<struct lispVar> Accept(VisitorStmt *visitor){vector<struct lispVar> lv; return lv;};
};

class Block;
class Class;
class Expression;
class Function;
class Cond;
class Print;
class Return;
class Var;

class VisitorStmt : public Stmt 
{
    public:
        ~VisitorStmt(){}
        virtual vector<struct lispVar> VisitBlockStmt(Block* stmt){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitClassStmt(Class* stmt){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitExpressionStmt(Expression* stmt){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitFunctionStmt(Function* stmt){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitCondStmt(Cond* stmt){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitPrintStmt(Print* stmt){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitReturnStmt(Return* stmt){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitVarStmt(Var* stmt){vector<struct lispVar> lv; return lv;};
        
};

class Block : public Stmt
{
    public:
        list<Stmt*> stmts;

        Block(list<Stmt*> s)
        {
            stmts = s;
        }

        vector<struct lispVar> Accept(VisitorStmt *visitor)
        {
            return visitor->VisitBlockStmt(this);
        }
};

class Class : public Stmt 
{
    public:
        Token name;
        //Variable* superclass;
        list<Function*> methods;

    Class(Token n, list<Function*> m)
    {
        name = n;
        //superclass = s;
        methods = m;
    }

    vector<struct lispVar> Accept(VisitorStmt* visitor)
    {
        return visitor->VisitClassStmt(this);
    }
};

class Expression : public Stmt
{
    public:
        Expr* expression;

        Expression(Expr* e)
        {
            expression = e;
        }

        vector<struct lispVar> Accept(VisitorStmt* visitor)
        {
            return visitor->VisitExpressionStmt(this);
        }
};

class Function : public Stmt
{
    public:
        Token name;
        list<Token> params;
        list<Stmt*> body;

        Function(Token n, list<Token> p, list<Stmt*> b)
        {
            name = n;
            params = p;
            body = b;
        }

        vector<struct lispVar> Accept(VisitorStmt* visitor)
        {
            return visitor->VisitFunctionStmt(this);
        }
};

class Cond : public Stmt
{
    public:
        list<Expr*> conditions;
        list<Stmt*> conditionbranches;
        

        Cond(list<Expr*> c, list<Stmt*>  cb)
        {
            conditions = c;
            conditionbranches = cb;
        }

        vector<struct lispVar> Accept(VisitorStmt* visitor)
        {
            return visitor->VisitCondStmt(this);
        }
};

class Print : public Stmt
{
    public:
        Expr* expression;

        Print(Expr* e)
        {
            expression = e;
        }

        vector<struct lispVar> Accept(VisitorStmt* visitor)
        {
            return visitor->VisitPrintStmt(this);
        }
};

class Return : public Stmt
{
    public:
        Expr* value;

        Return(Expr* v)
        {
            value = v;
        }

        vector<struct lispVar> Accept(VisitorStmt* visitor)
        {
            return visitor->VisitReturnStmt(this);
        }
};

class Var : public Stmt 
{
    public:
        Token name;
        Expr* init;

        Var(Token n, Expr* i)
        {
            name = n;
            init = i;
        }

        vector<struct lispVar> Accept(VisitorStmt* visitor)
        {
            return visitor->VisitVarStmt(this);
        }
};

