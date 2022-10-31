#include <string>
#include <list>
#include <map>
#include "token.cpp"


using namespace std;



class lispScanner
{
    public:
        lispScanner(string s);
        list<Token> scanTokens();

    private:
        int start = 0;
        int current = 0;
        int line = 1;

        string lispCode;

        list<Token> lispTokens;

        map <string, TokenType> keywords = 
        {
            {},
        };

        void scanToken();
        void identifier();
        void addToken(TokenType t);
        void addToken(TokenType t, string tokenLiteral);
        void addTokenDigit();
        void addTokenString();

        //helper methods
        char advance();
        char lookAhead();
        char lookAheadAhead();

        bool isAlpha(char c);
        bool isDigit(char c);
        bool isNotEnd();
        bool match(char c);
};


lispScanner::lispScanner(string s)
{
    lispCode = s;
}

list<Token>
lispScanner::scanTokens()
{
    char advanceChar = advance();

    switch (ch) {
        case '(': 
            addToken(LEFT_PAREN); break;
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
        case ';': 
            addToken(SEMICOLON); break;
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
            addTokenString();
            break;

        default:
            if(isDigit(ch))
            {
                addTokenDigit();
            }  
            else if(isAlpha(ch))
            {
                identifier();
            }
            else
            {
                /// @brief Error message handling. Should redirect to lox.error //
                cout << line << ", " << "Unexpected character. " << endl;
            }

            break;
        }
}
