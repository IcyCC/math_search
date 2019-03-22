#pragma once

#include <map>
#include <string>
#include <vector>
#include "lex.h"

class ExpNode
{
  std::string value;
  ExpNode &left_node;
  ExpNode &right_node;
  ExpNode &parent_node;
};

class WordStack
{
public:
  ExpNode parser(std::vector<TokenType>);
};