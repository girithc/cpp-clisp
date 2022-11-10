
#include <iostream>
#include <list>
#include <string.h>
#include <string>


#include "token.cpp"

using namespace std;


class Visitor;
class Expr 
{
    public:
        virtual ~Expr(){};
        virtual list<string> Accept(Visitor *visitor){return {""};};
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
        virtual list<string> VisitAssignExpr(Assign *expr) {return {""};};
        virtual list<string> VisitBinaryExpr(Binary *expr) {return {""};};
        virtual list<string> VisitCallExpr(Call *expr){return {""};} ;
        virtual list<string> VisitGetExpr(Get *expr) {return {""};};
        virtual list<string> VisitGroupingExpr(Grouping *xpr) {return {""};};
        virtual list<string> VisitLiteralExpr(Literal *expr) {return {""};};
        virtual list<string> VisitLogicalExpr(Logical *expr) {return {""};};
        virtual list<string> VisitSetExpr(Set *expr) {return {""};};
        virtual list<string> VisitThisExpr(This *expr) {return {""};};
        virtual list<string> VisitVariableExpr(Variable *expr) {return {""};};

        virtual list<string> VisitConsExpr(Cons *expr){return {""};};
        virtual list<string> VisitCarExpr(Car *expr){return {""};};
        virtual list<string> VisitCdrExpr(Cdr *expr){return {""};};
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

        list<string> Accept(Visitor *visitor)        
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

        list<string> Accept(Visitor *visitor)       
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

        list<string> Accept(Visitor *visitor)       
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

        list<string> Accept(Visitor *visitor)       
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

        list<string> Accept(Visitor *visitor)       
        {   return visitor->VisitCdrExpr(this);
        }
};


class Call : public Expr
{
    public:
        Expr* callee;
        Token paren;
        list<Expr*> arguments;

        Call(Expr* c, Token p, list<Expr*> as)
        {   callee = c;
            this->paren = p;
            arguments = as;
        }

        list<string> Accept(Visitor *visitor)       
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

        list<string> Accept(Visitor *visitor)        
        {   return visitor->VisitGetExpr(this);}

};


class Grouping : public Expr
{
    public:
        Expr* expression;
        Grouping(Expr* e){   expression = e;}
        list<string> Accept(Visitor *visitor)        
        {   return visitor->VisitGroupingExpr(this);}
};


class Literal : public Expr
{
    public:
        list<string> value;
        Literal(list<string> v)
        {   value = v;}
        list<string> Accept(Visitor *visitor)       
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

        list<string> Accept(Visitor *visitor)       
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

        list<string> Accept(Visitor *visitor)
        {   return visitor->VisitSetExpr(this);}

};


class This : public Expr
{
    public:
        Token keyword;

        This(Token k)
        {   keyword = k;}

        list<string> Accept(Visitor *visitor)        
        {   return visitor->VisitThisExpr(this);}

};



class Variable : public Expr
{
    public:
        Token name;

        Variable(Token n)
        {   name = n;}

        list<string> Accept(Visitor *visitor)      
        {   return visitor->VisitVariableExpr(this);}

};





