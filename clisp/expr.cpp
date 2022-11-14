
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
class Get;
class Grouping;
class Literal;
class Logical;
class Set;
class This;
class Variable;

class Cons;
class Car;
class Cdr;

class Visitor : public Expr
{
    public:
        ~Visitor() {}
        virtual vector<struct lispVar> VisitAssignExpr(Assign *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitBinaryExpr(Binary *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitCallExpr(Call *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitGetExpr(Get *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitGroupingExpr(Grouping *xpr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitLiteralExpr(Literal *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitLogicalExpr(Logical *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitSetExpr(Set *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitThisExpr(This *expr) {vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitVariableExpr(Variable *expr) {vector<struct lispVar> lv; return lv;};

        virtual vector<struct lispVar> VisitConsExpr(Cons *expr){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitCarExpr(Car *expr){vector<struct lispVar> lv; return lv;};
        virtual vector<struct lispVar> VisitCdrExpr(Cdr *expr){vector<struct lispVar> lv; return lv;};
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


class Get : public Expr
{
    public:
        Expr* object;
        Token name;

        Get(Expr* o, Token n)
        {   object = o;
            name = n;
        }

        vector<struct lispVar> Accept(Visitor *visitor)        
        {   return visitor->VisitGetExpr(this);}

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
        string value;
        Literal(string v)
        {   value = v;}
        vector<struct lispVar> Accept(Visitor *visitor)       
        {   return visitor->VisitLiteralExpr(this);}
};


class Logical : public Expr
{
    public:
        Expr* left;
        Token op;
        Expr* right;

        Logical(Expr* l, Token op, Expr* r)
        {   left = l;
            this->op = op;
            right = r;
        }

        vector<struct lispVar> Accept(Visitor *visitor)       
        {   return visitor->VisitLogicalExpr(this);}

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


class This : public Expr
{
    public:
        Token keyword;

        This(Token k)
        {   keyword = k;}

        vector<struct lispVar> Accept(Visitor *visitor)        
        {   return visitor->VisitThisExpr(this);}

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





