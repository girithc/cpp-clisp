#include <string>
#include <list>
#include <map>
#include <iostream>
#include <iterator>
#include "lispParser.cpp"


using namespace std;



class LispScanner
{
    public:
        LispScanner(string s);
        list<Token> scanTokens();

    private:
        int start = 0;
        int current = 0;
        int line = 1;

        string lispCode;

        list<Token> lispTokens;

        map <string, TokenType> keywords = 
        {
            {"false", FALSE},
            {"for", FOR},
            {"if", IF},
            {"print", PRINT},
            {"return", RETURN},
            {"this", THIS},
            {"true", TRUE},
            {"var", VAR},
            {"cons", CONS},
            {"cond", COND},
            {"cdr", CDR},
            {"car", CAR},
            {"set", SET},
            {"number?", ISNUMBER},
            {"symbol?", ISSYMBOL},
            {"list?", ISLIST},
            {"nil?", ISNIL},
            {"define", DEFINE}
        };

        void scanToken();

        void addToken(TokenType t);
        void addToken(TokenType tokentype, string tokenLiteral);
        void addTokenIdentifier();
        void addTokenDigit();
        void addTokenSymbol();

        //helper methods
        char advance();
        char lookAhead();
        char lookAheadAhead();

        bool isAlphaNum(char c);
        bool isAlpha(char c);
        bool isDigit(char c);
        bool isNotEnd();
        bool match(char c);

        int lenLispCode();
};


LispScanner::LispScanner(string s)
{
    lispCode = s;
}

list<Token>
LispScanner::scanTokens()
{
    while(isNotEnd())
    {
        start = current;
        scanToken();
    }
    lispTokens.push_back(*(new Token(TokenEOF,"","",line)));
    return lispTokens;
}

void
LispScanner::scanToken()
{
    char advanceChar = advance();
    cout << "Current char: " << advanceChar << " current:" << current << endl;
    switch (advanceChar) {
        case '(': 
            addToken(LEFT_PAREN);
            if(lookAhead() == ')') addToken(NIL);
             break;
        case ')': 
            addToken(RIGHT_PAREN); break;
        case '{': 
            addToken(LEFT_BRACE); break;
        case '}': 
            addToken(RIGHT_BRACE); break;
        case ',': 
            addToken(COMMA); break;
        case '.': 
            addToken(DOT); break;
        case '-': 
            addToken(MINUS); break;
        case '+': 
            addToken(PLUS); break;
        case '*': 
            addToken(STAR); break;
        case '!':
            if (match('='))
                addToken(BANG_EQUAL);
            else 
                addToken(BANG);
            break;
        case '=':
            if (match('='))
                addToken(EQUAL_EQUAL);
            else 
                addToken(EQUAL);
            break;
        case '<':
            if (match('='))
                addToken(LESS_EQUAL);
            else 
                addToken(LESS);
            break;
        case '>':
            if (match('='))
                addToken(GREATER_EQUAL);
            else 
                addToken(GREATER);
            break;
        case ';':
            if (match(';')) {
                // a line of comment
                while(isNotEnd() && lookAhead() != '\n')
                    advance();
            } 
            else {
                addToken(SLASH);
            }
            break;
        case '/':
            if (match('/')) {
                // a line of comment
                while(isNotEnd() && lookAhead() != '\n')
                    advance();
            } 
            else {
                addToken(SLASH);
            }
            break;


        case ' ':
        case '\r':
        case '\t':
            //whitespace
            break;

        case '\n':
            line = line + 1;
            break;

        //STRING
        case '"':
            addTokenSymbol();
            break;
        case '\'':
            if(match('t'))
                addToken(TRUE);
            break;

        default:
            if(isDigit(advanceChar))
            {
                addTokenDigit();
            }  
            else if(isAlpha(advanceChar))
            {
                addTokenIdentifier();
            }
            else
            {
                cout << "Unexpected character:  "<< advanceChar << " at line " << line << endl;
            }

            break;
        }
}

void
LispScanner::addToken(TokenType t)
{
    addToken(t,"");
}

void 
LispScanner::addToken(TokenType tokentype, string tokenLiteral)
{
    cout << "   AddToken(" << enum_str[tokentype] << "," << tokenLiteral << "," << lispCode.substr(start,lenLispCode()) << ","  << line << ")" << endl;
    
    if(enum_str[tokentype] == "SYMBOL")
        lispTokens.push_back(*(new Token(tokentype,tokenLiteral,lispCode.substr(start,lenLispCode()),line)));
    
    else 
        lispTokens.push_back(*(new Token(tokentype,lispCode.substr(start,lenLispCode()),tokenLiteral,line)));
    
}

void 
LispScanner::addTokenIdentifier()
{
        while(isAlphaNum(lookAhead())) advance();

        string s = lispCode.substr(start, lenLispCode());
        
        if (keywords.find(s) != keywords.end())
        {
            auto it = keywords.find(s);
            TokenType tType = it->second;
            addToken(tType);
        }
        else
        {
            addToken(IDENTIFIER);
        }
}

void 
LispScanner::addTokenDigit()
{
    while(isDigit(lookAhead()))
    {
        advance();
        //look for decimal numbers. Maximum munch
        if(isDigit(lookAheadAhead() && lookAhead()=='.')) advance();
    }
    addToken(NUMBER,lispCode.substr(start,lenLispCode()));
}

void 
LispScanner::addTokenSymbol()
{
    while(isNotEnd() && lookAhead()!='"')
    {
        cout << "   consuming string" << endl;
        if(lookAhead()!='\n') advance();
        line ++;
    }
    //unterminated string
    if(!isNotEnd())
    {
        cout << "Unterminated symbol. Line: "<< line << endl;
        return;
    }
    
    advance();
    string symbolLispCode = lispCode.substr(start+1, (current-1-(start+1)));
    //cout << "   symbolLispCode:" << symbolLispCode << endl;
    addToken(SYMBOL, symbolLispCode);
}

char
LispScanner::advance()
{
    //advance current
    current++;
    return lispCode[current-1];
}

char
LispScanner::lookAhead()
{
    if(!isNotEnd()) return '\0';
    return lispCode[current];
}

char 
LispScanner::lookAheadAhead()
{
    if(lispCode.length() < (current+1)) return '\0';
    return lispCode[current+1];
}

bool
LispScanner::isAlphaNum(char c)
{
    return (isAlpha(c) || isDigit(c));
}

bool
LispScanner::isAlpha(char c)
{

    if (c >= 'a' && c <= 'z') return true;
    if (c >= 'A' && c <= 'Z') return true;
    if (c == '_' || c == '?') return true;
    return false;
}

bool 
LispScanner::isDigit(char c)
{
    if(c<='9')
    {
        if(c>='0') 
            return true;
    }
    return false;
}

bool
LispScanner::isNotEnd()
{
    return (current < lispCode.length());
}

bool
LispScanner::match(char c)
{
    if(isNotEnd())
    {
        if(lispCode[current]==c)
        {
            current++;
            return true;
        } 
    }
    return false;
}


int
LispScanner::lenLispCode()
{
    return current-start;
}

