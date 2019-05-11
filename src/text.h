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


void GetAllKeyWord(AbcStore *store)  //Get All keywords from the data
{

	for(std::vector<TextBlock>::iterator it = store->data.begin();it!= store->data.end();it++)
	{
		KeyWordGather.push_back(it->title);
	}

}
void SetKeyWordPosition(std::vector<std::string> Key_word,TextBlock *data)
{
	KeyWord kw;
	int len,position;
	len = Key_word.size();
	
	data->depot.clear();
	std::vector<KeyWord>().swap(data->depot);   //clear vector data;

	for(int i = 0;i<len;i++)
	{
		position = data->raw.find(Key_word[i]);
		if( position != data->raw.npos)
		{
			kw.word = Key_word[i];
			kw.len = Key_word[i].length();
			kw.point = position;
			data->depot.push_back(kw);
		}
	}
}

void SetKeyWordPositionAll(AbcStore *store)
{
	GetAllKeyWord(store);
	int len = store->data.size();
	for(int i = 0;i<len;i++)
	{
		SetKeyWordPosition(KeyWordGather,store->data[i]);
	}
}