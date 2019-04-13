#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include "util.h"

class TextBlock
{
public:
  enum BlockType
  {
    NATURE,
    CONCEPT,
    EXERCISES,
    TEXT
  };
  int id;
  std::string title;
  std::string raw;
  BlockType type;
  std::string Dumps();
  TextBlock(int _id, std::string _title, std::string _raw, BlockType _type);
};

std::vector<TextBlock> ParseFromLatex(std::string filepath);
