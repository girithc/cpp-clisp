#include "tokentype.cpp"
#include <string>

using namespace std;


class Token
{
    public:
        Token();
        Token(TokenType t, string lexeme, string literal, int line);
        string getTokenType();
        string getTokenLexeme();
        string getTokenLiteral();

    private:
        TokenType t;
        string lexeme;
        string literal;
        int line;
};

Token::Token()
{
    this->line = 0;
    this->lexeme = "";
    this->literal = "";
}

Token::Token(TokenType t, string lexeme, string literal, int line)
{
    this->t = t;
    this->lexeme = lexeme;
    this->literal = literal;
    this->line = line;
}

string
Token::getTokenType()
{
    return enum_str[this->t];
}

string 
Token::getTokenLexeme()
{
    return this->lexeme;
}

string 
Token::getTokenLiteral()
{
    return this->literal;
}