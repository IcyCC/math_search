//
// Created by 苏畅 on 2019/5/12.
//

#ifndef MATH_SEARCH_KEYWORD_H
#define MATH_SEARCH_KEYWORD_H

#include "text.h"
#include "store.h"

  //all keyword gather
void GetAllKeyWord(AbcStore *store);  // need AbcStore,the All keyword will input KeyWordGather

void SetKeyWordPosition(std::vector<std::string>& Key_word,TextBlock *data);
// 其中的Key_word 是关键字符集，你可以之间输入上面的KeyWordGather 或者在你使用的时候自己新创一个vector，最后结果会把TextBlock中的depot存入所有有的关键词

void SetKeyWordPositionAll(AbcStore *store);//for all text block set keyword position

void KeyWordToFile(AbcStore *store,std::string path);

#endif //MATH_SEARCH_KEYWORD_H
