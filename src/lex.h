#pragma once

#include <map>
#include <string>
#include <vector>

enum TokenMeta
{
  VAR,
  OP
};

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

  VVAR,
};

class Token
{
public:
  TokenType type;    //类型
  TokenMeta meta;    //元类型
  std::string value; //值

  Token(TokenType _type, TokenMeta _meta, std::string _value)
  {
    type = _type;
    meta = _meta;
    value = _value;
  };
};

class Lexer
{
private:
  std::map<TokenType, std::string> rules; // 规则
public:
  std::vector<Token> parser(std::string raw){}; // 解析
};
