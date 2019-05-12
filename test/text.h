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
    EXAMPLE,
    TEXT
  };
  int id;
  std::string chapter;
  std::string title;
  std::string raw;
  BlockType type;
  std::string Dumps();
  inline TextBlock(int _id, std::string _chapter, std::string _title, std::string _raw, BlockType _type) {
    id = _id;
    chapter = _chapter;
    title = _title;
    raw = _raw;
    type = _type;
  };
};

std::vector<std::string> paserLatex2String(std::regex re, std::string raw);
std::vector<TextBlock> ParseFromLatex(std::string filepath);
