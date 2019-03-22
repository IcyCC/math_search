#pragma once

#include <map>
#include <string>

enum TokenType
{
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    LT,
    GT,
    EQ,
    LTE,
    GTE,
    NEQ,

    LPAREN,
    RPAREN,
    LBRACKET,
    RBRACKET,

    FUNC,

    VAR,
};

class Token
{
  public:
    TokenType type;    //类型
    std::string value; //值
};

class Lexer
{
  private:
    std::map<TokenType, std::string> rules; // 规则
  public:
    j' parser(std::string raw); // 解析
};
