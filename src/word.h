#pragma once

#include <map>
#include <string>
#include <vector>
#include "lex.h"

enum TreeNodeType
{
  ROOT,
  NORMAL,
  EMPTY,
};

class ExpNode
{
public:
  int id;
  std::string value;
  Token *token;
  ExpNode *left_node;
  ExpNode *right_node;
  ExpNode *parent_node;
  TreeNodeType type;
};

class WordStack
{
public:
  ExpNode parser(std::vector<TokenType>);
};