#pragma once
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
    TokenType type;    //����
    TokenMeta meta;    //Ԫ����
    std::string value; //ֵ
};

class Lexer
{
  private:
    	std::map<TokenType, std::string> rules; // ����
  public:
    	std::vector<Token> parser(std::string raw); // ����
};
