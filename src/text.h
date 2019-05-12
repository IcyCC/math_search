#pragma once

#include <string>
#include <vector>
#include"store.h"
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
  
  std::vector<KeyWord> depot;    // text keyword gether
  
  inline TextBlock(int _id, std::string _title, std::string _raw, BlockType _type) {
    id = _id;
    title = _title;
    raw = _raw;
    type = _type;
  } ;
};

class KeyWord
{
  public:
    std::string word;
    int point;
    int len;
};

std::vector<std::string> KeyWordGather;  //all keyword gather
void GetAllKeyWord(AbcStore *store);  // need AbcStore,the All keyword will input KeyWordGather

void SetKeyWordPosition(std::vector<std::string> Key_word,TextBlock data); 
// 其中的Key_word 是关键字符集，你可以之间输入上面的KeyWordGather 或者在你使用的时候自己新创一个vector，最后结果会把TextBlock中的depot存入所有有的关键词

void SetKeyWordPositionAll(AbcStore *store);//for all text block set keyword position


std::vector<std::string> paserLatex2String(std::regex re, std::string raw);
std::vector<TextBlock> ParseFromLatex(std::string filepath);
