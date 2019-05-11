#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <string.h>
using namespace std;
using std::string;

enum TokenMeta
{
    VAL=0,
    OP,
};

enum TokenType
{
    ADD=0,
    SUB,
    MUL,
    DIV,

    LT,
    GT,
    EQ,
    LTE,
    GTE,
    NEQ,
    APPROX,

    LPAREN,// (
    RPAREN,
    LBRACKET,// {
    RBRACKET,

	ABS,// |
	INV,// ^
	
	
	VAR
};

class Token
{
  public:
    TokenType type;    //类型
    TokenMeta meta;    //元类型
    std::string value; //值
};

class Lexer
{
  private:
    	std::map<TokenType, std::string> rules; // 规则
  public:
    	std::vector<Token> parser(std::string raw); // 解析
};
