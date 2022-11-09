
#include "stmt.cpp"

#include <string>
#include <iterator>
#include <list>

using namespace std;

class lispParser
{
    public:
    
    lispParser(list<Token> t);
    list<Stmt*> parse();
    
    private:
    
    int current = 0;
    list<Token> tokens;

    Stmt* declaration();
    Stmt* detail();
    Stmt* setDeclaration();
    Stmt* printDeclaration();

    Expr* lispExpression();
    Expr* lispAssignment();
    Expr* lispPrimary();

    Expr* L();
    Expr* I();
    Expr* S();
    Expr* P();

    //helper methods
    void advanceLispToken();
    bool isNotEnd();
    bool check(TokenType tokentype);
    bool match(list<TokenType> tokentypes);
    Token lookAhead();
    Token getLispToken(int index);
    Token consumeLispToken(TokenType tokentype, string message);
};

lispParser::lispParser(list<Token> t)
{
    tokens = t;
}

list<Stmt*>
lispParser::parse()
{
    list<Stmt*> sList;
    while(isNotEnd())
    {
        cout << "parsing stmt...  curr:" << current << endl << endl;
        sList.push_back(declaration());
    }
        
    return sList;
}

Stmt*
lispParser::declaration()
{
    cout << "Entered declaration: " << getLispToken(current-1).getTokenType() << endl;
    Token left_paren = consumeLispToken(LEFT_PAREN, "Expect '(' at the start of a statment.");
    //cout << "   After consumeLispToken. Current: " << current << endl;
   
    Stmt* stmtDetail = detail();
    cout << "   Entered declaration again" << endl;

    Token right_paren = consumeLispToken(RIGHT_PAREN, "Expect ')' at the end of a statment.");
    //cout << "   After consumeLispToken. Current: " << current << endl;

    Stmt* stmtplaceholder;
    return stmtplaceholder;
}

Stmt*
lispParser::detail()
{
    cout << "Entered detail" << endl;

    list<TokenType> set, print, define;

    set.push_back(SET);
    print.push_back(PRINT);
    define.push_back(DEFINE);
    
    if(match(set))
    {
        cout << "Entered SET" << endl;
        return setDeclaration();
    }
    else if(match(print))
    {
        cout << "Entered PRINT" << endl;
        return printDeclaration();
    }
    else if(match(define))
    {
        cout << "Entered DEFINE" << endl;
    }


    Stmt* stmtplaceholder;
    return stmtplaceholder;
}

Stmt* 
lispParser::setDeclaration()
{
    cout << "   Entered setDeclaration" << endl;
    
    Token id = consumeLispToken(IDENTIFIER, "Expect a variable name as first argument in SET.");
    Expr* idValue = lispExpression();

    cout << "   Entered setDeclaration again" << endl;
    
    cout << "   created VAR" << endl;
    return new Var(id, idValue);
}

Stmt*
lispParser::printDeclaration()
{
    Expr* expr = lispExpression();

    cout << "   created PRINT" << endl;
    return new Print(expr);
}


Expr* 
lispParser::lispExpression()
{
    list<TokenType> arithmetic, cons, cadr, symnum;
    arithmetic.push_back(PLUS);
    arithmetic.push_back(MINUS);
    arithmetic.push_back(STAR);
    arithmetic.push_back(SLASH);
    arithmetic.push_back(EQUAL);
    arithmetic.push_back(LESS);
    arithmetic.push_back(GREATER);
    cons.push_back(CONS);
    cadr.push_back(CAR);
    cadr.push_back(CDR);
    symnum.push_back(NUMBER);
    symnum.push_back(SYMBOL);
    symnum.push_back(LIST);
    symnum.push_back(NIL);

    if(match(arithmetic))
    {
        cout << "Entered ARITHMETIC" << endl;
        Token op = getLispToken(current-1);
        Expr* a = lispExpression();
        Expr* b = lispExpression();

        cout << "   Created Binary(arithmetic)" << endl;
        return new Binary(op, a, b);
    } 
    else if(match(cons))
    {
        cout << "   Entered CONS" << endl;
        // (cons a b)

        Token cons = getLispToken(current-1);
        //cout << "   token:" << cons.getTokenType() << endl;
        Expr* a = lispExpression();
        Expr* b = lispExpression();

        cout << "   created Cons" << endl;
        return new Cons(cons, a, b);
    }
    else if(match(cadr))
    {
        cout << "Entered CAR/CDR" << endl;

        Token cadr = getLispToken(current-1);
        Expr* a = lispExpression();

        
        
        if(cadr.getTokenType() == enum_str[CAR])
        {
            cout << "   created CAR" << endl;
            return new Car(cadr,a);
        } 
        else
        {
            cout << "   created CDR" << endl;
            return new Cdr(cadr,a);
        }
        
    }
    else if(match(symnum))
    {
        cout << "Entered SYMNUM" << endl;
    }

    return lispAssignment();
}
Expr*
lispParser::lispAssignment()
{
    return lispPrimary();
}
Expr* 
lispParser::lispPrimary()
{
    cout << "   Entered lispPrimary" << endl;

    list<TokenType>symnum, id, lispExpr;
    symnum.push_back(SYMBOL);
    symnum.push_back(NUMBER);
    id.push_back(IDENTIFIER);
    lispExpr.push_back(LEFT_PAREN);
    
    if(match(symnum))
    {
        cout << "       matched symnum: " << getLispToken(current-1).getTokenType()<< endl;
        Token symnumToken = getLispToken(current-1);
        cout << "       created LITERAL: " << symnumToken.getTokenLexeme() << endl;
        return new Literal(symnumToken.getTokenLexeme());
    }
    else if(match(id))
    {
        cout << "       matched identifier: " << getLispToken(current-1).getTokenLexeme()<< endl;
        cout << "       created VARIABLE" << endl;
        return new Variable(getLispToken(current-1));
    }
    else if (match(lispExpr))
    {
        /* repeat process */
        cout << "       matched another lispExpr" << endl;
        Expr* lispExpr = lispExpression();

        Token right_paren = consumeLispToken(RIGHT_PAREN, "Expect a ')' at the end of a lisp expression.");
        return lispExpression();
    }
    




    Expr* exprplaceholder;
    return exprplaceholder;
}


//helper methods
//@brief move 1 step forward. increment current.
void
lispParser::advanceLispToken()
{
    if(isNotEnd()) this->current += 1;
    else throw invalid_argument("Reached end of file.");
}
//@brief end of file
bool
lispParser::isNotEnd()
{
    //<< "       lookAhead: " << lookAhead().getTokenType() << endl;
    return (lookAhead().getTokenType() != "TokenEOF");
}

//@brief check if tokentype matches given tokentype 
bool
lispParser::check(TokenType tokentype)
{
    cout << "   Entered check" << endl;

    if (isNotEnd()) return lookAhead().getTokenType() == enum_str[tokentype];
    else return false;
}

//@brief check if tokentype matches list of tokentypes 
bool
lispParser::match(list<TokenType> tokentypes)
{
    cout << "   Entered match" << endl << "    ";

    list<TokenType>::iterator i;
    for (i = tokentypes.begin(); i != tokentypes.end(); i++)
    {
        if(check(*i))
        {
            advanceLispToken();
            return true;
        }
    }
    return false;
}

//@brief look for matching tokens
Token
lispParser::lookAhead()
{
    list<Token>::iterator i;

    int tokenIndexCounter = 0;
    for (i = tokens.begin(); i != tokens.end(); i++)
    {
        if(tokenIndexCounter == this->current) return *i;
        tokenIndexCounter += 1;
    }
    return Token();
}

//@brief get lisp token at index provided
Token 
lispParser::getLispToken(int index)
{
    list<Token>::iterator i;
    int tokenIndexCounter = 0;
    for (i = tokens.begin(); i != tokens.end(); i++)
    {
        if(current == 0) return *i;
        if(tokenIndexCounter == (index)) return *i;
        tokenIndexCounter += 1;
    }
    return Token();
}

//@brief check if tokentype from user matches expected tokentype. move 1 step forward. 
        //else throw error.
Token 
lispParser::consumeLispToken(TokenType tokentype, string message)
{
    cout << "   Entered consumeLispToken" << endl << "  ";

    if(check(tokentype))
    {
        Token token = getLispToken(current);
        advanceLispToken();
        return token;
    }

    throw invalid_argument(message);
}