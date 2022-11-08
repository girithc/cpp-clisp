#include <string>
#include <list>
#include "token.cpp"


class lispVisitor;
class lispExpr
{
    public:
    
    virtual ~lispExpr(){};
    virtual std::string Accept(lispVisitor* lispVisitor){return "";};

};

class Assign;
class Binary;
class Call;
class Get;
class Grouping;
class Literal;
class Logical;
class Set;
class Super;
class This;
class Unary;
class Variable;

class lispVisitor : public lispExpr
{
    public:
        ~lispVisitor() {}
        virtual std::string VisitAssignlispExpr(Assign *lispExpr) {return "";};
        virtual std::string VisitBinarylispExpr(Binary *lispExpr) {return "";};
        virtual std::string VisitCalllispExpr(Call *lispExpr){return "";} ;
        virtual std::string VisitGetlispExpr(Get *lispExpr) {return "";};
        virtual std::string VisitGroupinglispExpr(Grouping *lispExpr) {return "";};
        virtual std::string VisitLiterallispExpr(Literal *lispExpr) {return "";};
        virtual std::string VisitLogicallispExpr(Logical *lispExpr) {return "";};
        virtual std::string VisitSetlispExpr(Set *lispExpr) {return "";};
        virtual std::string VisitSuperlispExpr(Super *lispExpr) {return "";};
        virtual std::string VisitThislispExpr(This *lispExpr) {return "";};
        virtual std::string VisitUnarylispExpr(Unary *lispExpr) {return "";};
        virtual std::string VisitVariablelispExpr(Variable *lispExpr) {return "";};
};


class Assign : public lispExpr
{
    public:
        Token name;
        lispExpr* value;

                Assign(Token n, lispExpr* v)
        {
            name = n;
            value = v;
        }

        string Accept(lispVisitor *lispVisitor)        
        {   return lispVisitor->VisitAssignlispExpr(this);
        }
};


class Binary : public lispExpr
{
    public:
        lispExpr* left;
        Token op;
        lispExpr* right;

        Binary(lispExpr* l, Token o, lispExpr* r)
        {   left = l;
            right = r;
            op = o;
        }

        string Accept(lispVisitor *lispVisitor)       
        {   return lispVisitor->VisitBinarylispExpr(this);
        }
};


class Call : public lispExpr
{
    public:
        lispExpr* callee;
        Token paren;
        list<lispExpr*> arguments;

        Call(lispExpr* c, Token p, list<lispExpr*> as)
        {   callee = c;
            this->paren = p;
            arguments = as;
        }

        string Accept(lispVisitor *lispVisitor)       
        {   return lispVisitor->VisitCalllispExpr(this);
        }

};


class Get : public lispExpr
{
    public:
        lispExpr* object;
        Token name;

        Get(lispExpr* o, Token n)
        {   object = o;
            name = n;
        }

        string Accept(lispVisitor *lispVisitor)        
        {   return lispVisitor->VisitGetlispExpr(this);}

};


class Grouping : public lispExpr
{
    public:
        lispExpr* lispExpression;
        Grouping(lispExpr* e){   lispExpression = e;}
        string Accept(lispVisitor *lispVisitor)        
        {   return lispVisitor->VisitGroupinglispExpr(this);}
};


class Literal : public lispExpr
{
    public:
        string value;
        Literal(string v)
        {   value = v;}
        string Accept(lispVisitor *lispVisitor)       
        {   return lispVisitor->VisitLiterallispExpr(this);}
};


class Logical : public lispExpr
{
    public:
        lispExpr* left;
        Token op;
        lispExpr* right;

        Logical(lispExpr* l, Token op, lispExpr* r)
        {   left = l;
            this->op = op;
            right = r;
        }

        string Accept(lispVisitor *lispVisitor)       
        {   return lispVisitor->VisitLogicallispExpr(this);}

};

class Set : public lispExpr
{
    public:
        lispExpr* object;
        Token name;
        lispExpr* value;

        Set(lispExpr* o, Token n, lispExpr* v)
        {   object = o;
            name = n;
            value = v;
        }

        string Accept(lispVisitor *lispVisitor)
        {   return lispVisitor->VisitSetlispExpr(this);}

};


class Super : public lispExpr
{
    public:
        Token keyword;
        Token method;

        Super(Token k, Token m)
        {   keyword = k;
            method = m;
        }

        string Accept(lispVisitor *lispVisitor)       
        {   return lispVisitor->VisitSuperlispExpr(this);}

};


class This : public lispExpr
{
    public:
        Token keyword;

        This(Token k)
        {   keyword = k;}

        string Accept(lispVisitor *lispVisitor)        
        {   return lispVisitor->VisitThislispExpr(this);}

};


class Unary : public lispExpr
{
    public:
        Token op;
        lispExpr* right;

        Unary(Token o, lispExpr* r)
        {   op = o;
            right = r;}

        string Accept(lispVisitor *lispVisitor)        
        {   return lispVisitor->VisitUnarylispExpr(this);}

};


class Variable : public lispExpr
{
    public:
        Token name;

        Variable(Token n)
        {   name = n;}

        string Accept(lispVisitor *lispVisitor)      
        {   return lispVisitor->VisitVariablelispExpr(this);}

};


