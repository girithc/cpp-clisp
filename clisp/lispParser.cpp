//#include "lispInterpreter.cpp"

#include <string>
#include <iterator>
#include <list>
#include "lispInterpreter.cpp"
#include <iostream>
#include <vector>

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
    Stmt* functionDetail();
    Stmt* setDeclaration();
    Stmt* condDeclaration();
    Stmt* condFunDeclaration();
    Stmt* printDeclaration();
    Stmt* functionDeclaration();
    Stmt* functionInstanceDeclaration();
    Stmt* returnDeclaration();
    list<Stmt*> functionBlock();

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
list<Stmt*> lispParser::parse()
{
    list<Stmt*> sList;
    while(isNotEnd())
    {
        //cout << "parsing stmt...  curr:" << current << endl << endl;
        sList.push_back(declaration());
    }
        
    return sList;
}
Stmt* lispParser::declaration()
{
    //cout << "Entered declaration: " << getLispToken(current-1).getTokenType() << endl;
    Token left_paren = consumeLispToken(LEFT_PAREN, "Expect '(' at the start of a statment.");
    ////cout << "   After consumeLispToken. Current: " << current << endl;
   
    Stmt* stmtDetail = detail();
    //cout << "   Entered declaration again" << endl;

    Token right_paren = consumeLispToken(RIGHT_PAREN, "Expect ')' at the end of a statment.");
    //cout << "   After consumeLispToken. Current: " << current << endl;

    //Stmt* stmtplaceholder;
    //return stmtplaceholder;
    return stmtDetail;
}
Stmt* lispParser::detail()
{
    //cout << "Entered detail" << endl;

    list<TokenType> set, cond, print, define, functionCall;

    set.push_back(SET);
    cond.push_back(COND);
    print.push_back(PRINT);
    define.push_back(DEFINE);
    functionCall.push_back(IDENTIFIER);
    
    if(match(set))
    {
        //cout << "Entered SET" << endl;
        return setDeclaration();
    }
    if(match(cond))
    {
        //cout << "Entered COND" << endl;
        return condDeclaration();
    }
    else if(match(print))
    {
        //cout << "Entered PRINT" << endl;
        return printDeclaration();
    }
    else if(match(define))
    {
        //cout << "Entered DEFINE" << endl;
        return functionDeclaration();
    }
    else if(match(functionCall))
    {
        //cout << "Entered FunctionCall" << endl;
        return functionInstanceDeclaration();
        //exit(1);
    }


    Stmt* stmtplaceholder;
    return stmtplaceholder;
}
Stmt* lispParser::functionDetail()
{
    //cout << "Entered function detail" << endl;
    list<TokenType> print, cadr, cons, yesorno, cond, functionCall;
    print.push_back(PRINT);
    cadr.push_back(CAR);
    cadr.push_back(CDR);
    cons.push_back(CONS);
    yesorno.push_back(ISNUMBER);
    yesorno.push_back(ISSYMBOL);
    yesorno.push_back(ISLIST);
    yesorno.push_back(ISNIL);
    cond.push_back(COND);
    functionCall.push_back(IDENTIFIER);

    if(match(print))
    {
        //cout << "Entered PRINT" << endl;
        return printDeclaration();
    }
    else if(match(cadr))
    {
        Token cadr = getLispToken(current-1);
        Expr* a = lispExpression();
        if(cadr.getTokenType() == enum_str[CAR])
        {
            //cout << "   created RETURN(Car)" << endl;
            return new Return(new Car(cadr,a));
        }   
        else //cdr
        {
            //cout << "   created RETURN(Cdr)" << endl;
            return new Return(new Cdr(cadr, a));
        }
    }
    else if(match(cons))
    {
        //cout << "Entered CONS" << endl;

        Token cons = getLispToken(current-1);
        ////cout << "   token:" << cons.getTokenType() << endl;
        Expr* a = lispExpression();
        Expr* b = lispExpression();

        //cout << "   created RETURN(Cons)" << endl;
        return new Return(new Cons(cons, a, b));

    }
    else if(match(yesorno))
    {
        //cout << "Entered YES/NO" << endl;
        
        Token yesno = getLispToken(current-1);
        Expr* value = lispExpression();

        if(yesno.getTokenType() == enum_str[ISNUMBER])
        {
            //cout << "   created ISNUMBER" << endl;
        }
        else if(yesno.getTokenType() == enum_str[ISSYMBOL])
        {
            //cout << "   created ISSYMBOL" << endl;
        }
        else if(yesno.getTokenType() == enum_str[ISLIST])
        {
            //cout << "   created ISLIST" << endl;
        }
        else if(yesno.getTokenType() == enum_str[ISNIL])
        {
            //cout << "   created ISNIL" << endl;
        }
        //cout << "   created Return" << endl;
        return new Return(new YesOrNo(yesno, value));
    }
    else if(match(cond))
    {
        //cout << "Entered COND" << endl;
        return condFunDeclaration();
        
    }
    else if(match(functionCall))
    {
        //cout << "Entered FunctionCall" << endl;
        return functionInstanceDeclaration();
        //exit(1);
    }
    return returnDeclaration();
}
Stmt* lispParser::setDeclaration()
{
    //cout << "   Entered setDeclaration" << endl;
    
    Token id = consumeLispToken(IDENTIFIER, "Expect a variable name as first argument in SET.");
    Expr* idValue = lispExpression();

    //cout << "   Entered setDeclaration again" << endl;
    
    //cout << "   created VAR" << endl;
    return new Var(id, idValue);
}
Stmt* lispParser::condDeclaration()
{
    list<Expr*> conditions;
    list<Stmt*> conditionbranches;
    while(!check(RIGHT_PAREN))
    {   //if else condition
        //cout << "       cond CONDITION" << endl;
        Token leftparen_condition = consumeLispToken(LEFT_PAREN, "Expect '(' at the start of condition.");
        Expr* lispcondition = lispExpression();
        Token rightparen_condition = consumeLispToken(RIGHT_PAREN, "Expect ')' at the start of condition.");

        //cout << "       cond BRANCH" << endl;
        Token leftparen2 = consumeLispToken(LEFT_PAREN, "Expect '(' at the start of result.");
        Stmt* branch = detail();
        Token rightparen2 = consumeLispToken(RIGHT_PAREN, "Expect ')' at the start of result.");
    
        conditions.push_back(lispcondition);
        conditionbranches.push_back(branch);
    }
    
    //cout << "   created COND" << endl;
    return new Cond(conditions,conditionbranches);
}
Stmt* lispParser::condFunDeclaration()
{
    //cout << "   Enter CondFunDeclaration " << endl;
    list<Expr*> conditions;
    list<Stmt*> conditionbranches;
    while(!check(RIGHT_PAREN))
    {   //if else condition
        //cout << "       cond CONDITION" << endl;
        Token leftparen_condition = consumeLispToken(LEFT_PAREN, "Expect '(' at the start of condition.");
        Expr* lispcondition = lispExpression();
        Token rightparen_condition = consumeLispToken(RIGHT_PAREN, "Expect ')' at the start of condition.");

        //cout << "       cond BRANCH" << endl;
        Token leftparen2 = consumeLispToken(LEFT_PAREN, "Expect '(' at the start of result.");
        Stmt* branch = functionDetail();
        Token rightparen2 = consumeLispToken(RIGHT_PAREN, "Expect ')' at the start of result.");
    
        conditions.push_back(lispcondition);
        conditionbranches.push_back(branch);
    }
    
    //cout << "   created COND" << endl;
    return new Cond(conditions,conditionbranches);
}
Stmt* lispParser::printDeclaration()
{
    Expr* expr = lispExpression();

    //cout << "   created PRINT" << endl;
    return new Print(expr);
}
Stmt* lispParser::functionDeclaration()
{
    //cout << "   Entered functionDeclaration" << endl;
    Token functionName = consumeLispToken(IDENTIFIER, "Expect function name after 'define'");
    Token leftparen = consumeLispToken(LEFT_PAREN, "Expect '(' after function name.");
    list<Token> functionParameters;

    while(!check(RIGHT_PAREN))
    {
        //cout << "       consume Function Parameter" << endl;
        functionParameters.push_back(consumeLispToken(IDENTIFIER, "Expect a parameter name"));
    }
    Token rightParen = consumeLispToken(RIGHT_PAREN, "Expect ')' in function declaration");
    
    list<Stmt*> functionStmts = functionBlock();

    //cout << "   created FUNCTION" << endl;
    return new Function(functionName,functionParameters,functionStmts);
    //Stmt* placeholder;
    //return placeholder;
}
Stmt* lispParser::functionInstanceDeclaration()
{
    ////cout << getLispToken(current-1).getTokenLexeme() << endl;
    //cout << "   Enter functionInstanceDeclaration" << endl;
    Token functionName = getLispToken(current-1);
    list<Expr*> functionArguments;
    while(!check(RIGHT_PAREN))
    {
        functionArguments.push_back(lispExpression());
    }
    //cout << "   Created Expression(Function Instance)" << endl;
    return new Expression(new Call(functionName, functionArguments));
}
Stmt* lispParser::returnDeclaration()
{
    //cout << "   Return declaration" << endl;
    Expr* returnValue = lispExpression();

    //cout << "   created Return" << endl;
    return new Return(returnValue);
}
list<Stmt*> lispParser::functionBlock()
{
    //cout << "   Enter functionBlock" << endl;
    list<Stmt*> functionStmts;
    while(isNotEnd() && !check(RIGHT_PAREN))
    {
        Token leftparen = consumeLispToken(LEFT_PAREN,"Expect a '(' at the start of a function statement");
        functionStmts.push_back(functionDetail());
        Token rightparen = consumeLispToken(RIGHT_PAREN,"Expect a ')' at the start of a function statement");
    }
    return functionStmts;

    list<Stmt*> stmtsplaceholder;
    return stmtsplaceholder;
}

Expr* lispParser::lispExpression()
{
    list<TokenType> arithmetic, cons, cadr, yesorno;// symnum;
    arithmetic.push_back(PLUS);
    arithmetic.push_back(MINUS);
    arithmetic.push_back(STAR);
    arithmetic.push_back(SLASH);
    arithmetic.push_back(EQUAL);
    arithmetic.push_back(LESS);
    arithmetic.push_back(GREATER);
    arithmetic.push_back(GREATER_EQUAL);
    arithmetic.push_back(LESS_EQUAL);
    cons.push_back(CONS);
    cadr.push_back(CAR);
    cadr.push_back(CDR);
    yesorno.push_back(ISNUMBER);
    yesorno.push_back(ISSYMBOL);
    yesorno.push_back(ISLIST);
    yesorno.push_back(ISNIL);
    //symnum.push_back(NUMBER);
    //symnum.push_back(SYMBOL);
    //symnum.push_back(LIST);
    //symnum.push_back(NIL);

    if(match(arithmetic))
    {
        //cout << "Entered ARITHMETIC" << endl;
        Token op = getLispToken(current-1);
        Expr* a = lispExpression();
        //cout << "   Binary second expression start" << endl;
        Expr* b = lispExpression();

        //cout << "   Created Binary(arithmetic):" << op.getTokenType() << endl;
        return new Binary(op, a, b);
    } 
    else if(match(cons))
    {
        //cout << "   Entered CONS" << endl;
        // (cons a b)

        Token cons = getLispToken(current-1);
        //cout << "   token:" << cons.getTokenType() << endl;
        Expr* a = lispExpression();
        Expr* b = lispExpression();

        //cout << "   created Cons" << endl;
        return new Cons(cons, a, b);
    }
    else if(match(cadr))
    {
        //cout << "Entered CAR/CDR" << endl;

        Token cadr = getLispToken(current-1);
        Expr* a = lispExpression();

        
        
        if(cadr.getTokenType() == enum_str[CAR])
        {
            //cout << "   created CAR" << endl;
            return new Car(cadr,a);
        } 
        else
        {
            //cout << "   created CDR" << endl;
            return new Cdr(cadr,a);
        }
        
    }
    else if(match(yesorno))
    {
        //cout << "Entered YES/NO" << endl;
        
        Token yesno = getLispToken(current-1);
        Expr* value = lispExpression();

        if(yesno.getTokenType() == enum_str[ISNUMBER])
        {
            //cout << "   created ISNUMBER" << endl;
        }
        else if(yesno.getTokenType() == enum_str[ISSYMBOL])
        {
            //cout << "   created ISSYMBOL" << endl;
        }
        else if(yesno.getTokenType() == enum_str[ISLIST])
        {
            //cout << "   created ISLIST" << endl;
        }
        else if(yesno.getTokenType() == enum_str[ISNIL])
        {
            //cout << "   created ISNIL" << endl;
        }
        return new YesOrNo(yesno, value);
    }
    /*
    else if(match(symnum))
    {
        cout << "Entered SYMNUM" << endl;
    }
    */

    return lispAssignment();
}
Expr* lispParser::lispAssignment()
{
    return lispPrimary();
}
Expr* lispParser::lispPrimary()
{
    //cout << "   Entered lispPrimary:" << getLispToken(current).getTokenType()  << endl;

    list<TokenType>symnum, id, lispExpr, nil;
    symnum.push_back(SYMBOL);
    symnum.push_back(NUMBER);
    id.push_back(IDENTIFIER);
    lispExpr.push_back(LEFT_PAREN);
    nil.push_back(NIL);
    
    if(match(symnum))
    {
        //cout << "       matched symnum: " << getLispToken(current-1).getTokenType()<< endl;
        Token symnumToken = getLispToken(current-1);
        //cout << "       created LITERAL: " << symnumToken.getTokenLexeme() << endl;

        //struct lispVar lv;
        //lv.value = symnumToken.getTokenLexeme();
        
        //vector<struct lispVar> lispVarVector; 
        //lispVarVector.push_back(lv);
        
        return new Literal(symnumToken.getTokenLexeme());
    }
    else if(match(id))
    {
        //cout << "       matched identifier: " << getLispToken(current-1).getTokenLexeme() << endl;
        
        if(getLispToken(current-2).getTokenType() == enum_str[LEFT_PAREN])
        {
            //cout << "       entered CALL" << endl;
            Token callee = getLispToken(current-1);
            list<Expr*> functionArguments;
            while(!check(RIGHT_PAREN))
            {
                functionArguments.push_back(lispExpression());
            }
            //cout << "       created Call" << endl;
            return new Call(callee, functionArguments);
        }
        else
        {   
            //cout << "       created VARIABLE" << endl;
            return new Variable(getLispToken(current-1));
        }
    }
    else if (match(lispExpr))
    {
        /* repeat process */
        //cout << "       matched another lispExpr" << endl;
        Expr* lispExpr = lispExpression();

        Token right_paren = consumeLispToken(RIGHT_PAREN, "Expect a ')' at the end of a lisp expression.");
        return lispExpr;
    }
    else if(match(nil))
    {
        return new Literal("");
    }
    
    Expr* exprplaceholder;
    return exprplaceholder;
}

//helper methods
//@brief move 1 step forward. increment current.
void lispParser::advanceLispToken()
{
    if(isNotEnd()) this->current += 1;
    else throw invalid_argument("Reached end of file.");
}
//@brief end of file
bool lispParser::isNotEnd()
{
    //<< "       lookAhead: " << lookAhead().getTokenType() << endl;
    return (lookAhead().getTokenType() != "TokenEOF");
}
//@brief check if tokentype matches given tokentype 
bool lispParser::check(TokenType tokentype)
{
    //cout << "   Entered check" << endl;

    if (isNotEnd()) return lookAhead().getTokenType() == enum_str[tokentype];
    else return false;
}
//@brief check if tokentype matches list of tokentypes 
bool lispParser::match(list<TokenType> tokentypes)
{
    //cout << "   Entered match" << endl << "    ";

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
Token lispParser::lookAhead()
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
Token lispParser::getLispToken(int index)
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
Token lispParser::consumeLispToken(TokenType tokentype, string message)
{
    //cout << "   Entered consumeLispToken" << endl << "  ";

    if(check(tokentype))
    {
        Token token = getLispToken(current);
        advanceLispToken();
        return token;
    }

    throw invalid_argument(message);
}