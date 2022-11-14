#include <string>
#include <vector>
using namespace std;

enum TokenType 
{
        // Single-character tokens.
        LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
        COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

        // One or two character tokens.
        BANG, BANG_EQUAL,
        EQUAL, EQUAL_EQUAL,
        GREATER, GREATER_EQUAL,
        LESS, LESS_EQUAL,

        // Literals.
        IDENTIFIER, STRING, NUMBER,SYMBOL,

        // Keywords.
        AND, FALSE, FUNNAME, FOR, IF, ELSE, NIL, OR, DEFINE,
        PRINT, RETURN, THIS, TRUE, VAR, LIST,
        COND, CONS, CAR, CDR, SET, EQ, 
        ISNUMBER, ISSYMBOL, ISNIL,

        //others
        TokenEOF,
};

const string enum_str[] = 
{
        //Single Character 
        "LEFT_PAREN", "RIGHT_PAREN", "LEFT_BRACE", "RIGHT_BRACE",
        "COMMA", "DOT", "MINUS", "PLUS", "SEMICOLON", "SLASH", "STAR",
        "BANG", "BANG_EQUAL",
        "EQUAL", "EQUAL_EQUAL",
        "GREATER", "GREATER_EQUAL",
        "LESS", "LESS_EQUAL",
        "IDENTIFIER", "STRING", "NUMBER","SYMBOL",
        "AND", "FALSE", "FUNNAME", "FOR", "IF","ELSE", "NIL", "OR", "DEFINE",
        "PRINT", "RETURN", "THIS", "TRUE", "VAR", "LIST",  
        "COND", "CONS", "CAR", "CDR", "SET", "EQ",
        "ISNUMBER", "ISSYMBOL", "ISNIL",
        "TokenEOF",
};

struct lispVar 
{
        string value;
        vector<lispVar> next;
};