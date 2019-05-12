//
// Created by 苏畅 on 2019/5/12.
//

#include "keyword.h"


std::vector<std::string> KeyWordGather;

void GetAllKeyWord(AbcStore *store)  //Get All keywords from the data
{

    for(std::vector<TextBlock>::iterator it = store->data.begin();it!= store->data.end();it++)
    {
        KeyWordGather.push_back(it->title);
    }

}
void SetKeyWordPosition(std::vector<std::string>& Key_word,TextBlock *data)
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
        SetKeyWordPosition(KeyWordGather, &store->data[i]);
    }
}