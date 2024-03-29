
#include <iostream>
#include <list>
#include <string.h>
#include <string>
#include <vector>


#include "token.cpp"

using namespace std;


class Visitor;
class Expr 
{
    public:
        virtual ~Expr(){};
        virtual vector<struct lispVar> Accept(Visitor *visitor){vector<struct lispVar> lv; return lv;};
        //{accept(visitor);}s
        //virtual void accept(Visitor<R> *visitor);
};
class Assign;
class Binary;
class Call;
class Grouping;
class Literal;
class Set;
class Variable;
class Cons;
class Car;
class Cdr;
class YesOrNo;

class Visitor : public Expr
{
    public:
        ~Visitor() {}
        virtual vector<struct lispVar> VisitAssignExpr(Assign *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitBinaryExpr(Binary *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitCallExpr(Call *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitGroupingExpr(Grouping *xpr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitLiteralExpr(Literal *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitSetExpr(Set *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitVariableExpr(Variable *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitConsExpr(Cons *expr){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitCarExpr(Car *expr){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitCdrExpr(Cdr *expr){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitYesOrNoExpr(YesOrNo *expr){vector<struct lispVar> lv; return lv;};
};




class Assign : public Expr
{
    public:
        Token name;
        Expr* value;

        Assign(Token n, Expr* v)
        {
            name = n;
            value = v;
        }

        vector<struct lispVar> Accept(Visitor *visitor)        
        {   return visitor->VisitAssignExpr(this);
        }
};


class Binary : public Expr
{
    public:
        Expr* left;
        Token op;
        Expr* right;

        Binary(Token o, Expr* l, Expr* r)
        {   left = l;
            right = r;
            op = o;
        }

        vector<struct lispVar> Accept(Visitor *visitor)       
        {   return visitor->VisitBinaryExpr(this);
        }
};

class Cons : public Expr
{
    public:

        Token token;
        Expr* a;
        Expr* b;

        Cons(Token token, Expr* a, Expr* b)
        {   
            this->token = token;
            this->a = a;
            this->b = b;
        }

        vector<struct lispVar> Accept(Visitor *visitor)       
        {   return visitor->VisitConsExpr(this);
        }
};

class Car : public Expr
{
    public:

        Token token;
        Expr* a;

        Car(Token token, Expr* a)
        {   
            this->token = token;
            this->a = a;
        }

        vector<struct lispVar> Accept(Visitor *visitor)       
        {   return visitor->VisitCarExpr(this);
        }
};

class Cdr : public Expr
{
    public:

        Token token;
        Expr* a;

        Cdr(Token token, Expr* a)
        {   
            this->token = token;
            this->a = a;
        }

        vector<struct lispVar> Accept(Visitor *visitor)       
        {   return visitor->VisitCdrExpr(this);
        }
};


class Call : public Expr
{
    public:
        Token callee;
        list<Expr*> arguments;

        Call(Token c, list<Expr*> as)
        {   
            callee = c;
            arguments = as;
        }

        vector<struct lispVar> Accept(Visitor *visitor)       
        {   return visitor->VisitCallExpr(this);
        }

};


class Grouping : public Expr
{
    public:
        Expr* expression;
        Grouping(Expr* e){   expression = e;}
        vector<struct lispVar> Accept(Visitor *visitor)        
        {   return visitor->VisitGroupingExpr(this);}
};


class Literal : public Expr
{
    public:
        vector<struct lispVar> literalValue;
        Literal(string v)
        {
            struct lispVar lv;
            lv.value = v;
            this->literalValue.push_back(lv);
        }
        vector<struct lispVar> Accept(Visitor *visitor)       
        {   return visitor->VisitLiteralExpr(this);}
};


class Set : public Expr
{
    public:
        Expr* object;
        Token name;
        Expr* value;

        Set(Expr* o, Token n, Expr* v)
        {   object = o;
            name = n;
            value = v;
        }

        vector<struct lispVar> Accept(Visitor *visitor)
        {   return visitor->VisitSetExpr(this);}

};

class YesOrNo : public Expr
{
    public:
        Expr* value;
        Token name;

    YesOrNo(Token n, Expr* v)
    {
        name = n;
        value = v;
    }
    vector<struct lispVar> Accept(Visitor *visitor)
    {   return visitor->VisitYesOrNoExpr(this);}
};


class Variable : public Expr
{
    public:
        Token name;

        Variable(Token n)
        {   name = n;}

        vector<struct lispVar> Accept(Visitor *visitor)      
        {   return visitor->VisitVariableExpr(this);}

};





