//
// Created by 苏畅 on 2019/5/12.
//

#include "keyword.h"
#include <sstream>

static std::vector<std::string> KeyWordGather;

void GetAllKeyWordstd(std::vector<TextBlock> store)  //Get All keywords from the data
{

    for(std::vector<TextBlock>::iterator it = store.begin();it!= store.end();it++)
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



void SetKeyWordBlockToFile(std::vector<std::string>& Key_word,TextBlock data,const std::string file_string)
{


    std::ofstream OsWrite(file_string,std::ofstream::app);
    int len,position;
    char buf[1024];
    len = Key_word.size();

    for(int i = 0;i<len;i++)
    {
        position = data.raw.find(Key_word[i]);
        if( position != data.raw.npos)
        {
            memset(buf,0,sizeof(buf));
            sprintf(buf,"%s",Key_word[i].c_str());

            OsWrite << buf;
            OsWrite << std::endl;
        }
    }
    OsWrite.close();
}

void KeyWordToFile(std::vector<TextBlock> store,std::string path)
{

    int len = store.size();
     for(int i = 0;i<len;i++)
    {
        SetKeyWordBlockToFile(KeyWordGather,store[i],"/Users/suchang/Code/homework/math_search/KeyWord/" + store[i].title+".q");
    }
}