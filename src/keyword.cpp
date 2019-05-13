//
// Created by 苏畅 on 2019/5/12.
//

#include "keyword.h"
#include <sstream>

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


void SetKeyWordBlockToFile(std::vector<std::string>& Key_word,TextBlock *data,const std::string file_string)
{


    std::ofstream OsWrite(file_string,std::ofstream::app);
    int len,position;
    char buf[1024];
    len = Key_word.size();

    for(int i = 0;i<len;i++)
    {
        position = data->raw.find(Key_word[i]);
        if( position != data->raw.npos)
        {
            memset(buf,0,sizeof(buf));
            sprintf(buf,"%s %d %d",Key_word[i], Key_word[i].length(),position);

            OsWrite << buf;
            OsWrite << std::endl;
        }
    }
    OsWrite.close();
}

void KeyWordToFile(AbcStore *store,std::string path)  
{
    GetAllKeyWord(store);
    int len = store->data.size();
     for(int i = 0;i<len;i++)
    {
        SetKeyWordBlockToFile(KeyWordGather, &store->data[i], path + "/KeyWord/" + store->data[i].title);
    }
}