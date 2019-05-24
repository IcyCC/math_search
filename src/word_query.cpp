#include "word_query.h"

#include <algorithm>
#include <list>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <cassert>
#include <map>

#include "segment.h"
#include "utf.h"
#include "util.h"
#include "file_path.h"

using namespace query;
using namespace std;
using namespace utf;

// namespace fs = std::filesystem;

namespace
{

bool IsDelimiter(char32_t ch)
{
    return ch == U'.' || ch == U'。' || ch == U'\r' || ch == U'\n' || ch == 0;
}

// merge two sorted list into lhs
void merge_list(list<shared_ptr<u32string>>& lhs, const list<shared_ptr<u32string>>& rhs)
{
    auto lhs_it = lhs.begin();
    auto rhs_it = rhs.begin();
    while (lhs_it != lhs.end() && rhs_it != rhs.end())
    {
        if (*lhs_it < *rhs_it)
        {
            lhs_it = lhs.erase(lhs_it);
        }
        else if (*lhs_it > *rhs_it)
        {
            ++rhs_it;
        }
        else
        {
            ++lhs_it;
            ++rhs_it;
        }
    }
    if (lhs_it != lhs.end())
    {
        lhs.erase(lhs_it, lhs.end());
    }
}

pair<size_t, size_t> GetSummary(const shared_ptr<u32string>& content, size_t pos)
{
    size_t begin = pos, end = pos + 1;
    while (begin > 0 && !IsDelimiter((*content)[begin-1]))
        --begin;
    while (end < content->size() && !IsDelimiter((*content)[end]))
        ++end;
    return make_pair(begin, end - begin + 1);
}

} // namespace

WordQuery::WordQuery(const std::string& dirpath)
//    : word_segment_(WORD_FREQ_PATH)
{
    LoadContent(dirpath);

    // for every content
    for (const auto &content : contents_)
    {
//        word_segment_.SetContent(content);
        auto word_infos = ArticleSegment(*content);
        for (const auto &word_info : word_infos)
        {
            word_search_[word_info.word][content].push_back(word_info.index);
        }
    }
}

void WordQuery::LoadContent(const std::string& dirpath)
{
    for (auto &entry : GetAllFilenames(dirpath))
    {
        TextBlock text(entry);
        auto ptr = new u32string(to_utf32(text.raw));
        contents_.emplace_back(ptr);
        raw_textblock_.insert({ptr, text});
    }
}

WordQuery::QueryResult WordQuery::Query(const string& sentence) const
{
//    word_segment_.SetContent(sentence);
    auto word_infos = QuerySegment(sentence);
    auto it = word_infos.begin();
    list<shared_ptr<u32string>> content_list = get_list(it->word);

    for_each(++it, word_infos.end(), [&] (const query::WordSegment::WordInfo& word_info) {
        list<shared_ptr<u32string>> tmp = get_list(word_info.word);
        merge_list(content_list, tmp);
    });

    QueryResult result;

    if (content_list.empty())
        return result;

    for (const auto& word_info: word_infos)
    {
        const auto& map = word_search_.find(word_info.word)->second;
        for (const auto& content: content_list)
        {
            set<pair<size_t, size_t>> summaries;
            auto& pos_vec = map.find(content)->second;
            for (size_t pos: pos_vec)
            {
                auto pair = GetSummary(content, pos);
                // std::cout << "range:" << pair.first << " " << pair.second << "\n";
                if (auto it = summaries.find(pair); it == summaries.end())
                {
                    result[raw_textblock_.find(content.get())->second.raw].insert(
                            to_utf8(std::u32string(*content, pair.first, pair.second)));
//                    result[content][word_info.word].emplace_back(content->c_str() + pair.first, pair.second);
                    summaries.insert(pair);
                }
            }
        }
    }

    return result;
}

void WordQuery::SaveToFile(const std::string& path) const
{
    static bool has_visited = false;

    if (!has_visited)
    {
        for (std::size_t i = 0; i < contents_.size(); ++i)
        {
            content_index_[contents_[i]] = i;
        }
        has_visited = true;
    }
    ofstream openfile(path,ios::app);
    map<Word, map<shared_ptr<Article>, vector<size_t>>>::iterator it=word_search_.begin();
    while(it!=word_search_.end())
    {
        openfile<<it->first<<"~";
        map<std::shared_ptr<Article>, std::vector<std::size_t>>::iterator files=(it->second).begin();
        while(files!=(it->second).end())
        {
            openfile<<content_index_[files->first]<<"!";
            for(int i=0;i<(files->second).size;i++)
            {
                ofstream<<files->second[i];
                if(i!=(files->second).size-1)
                ofstream<<"@";
            }
        }
        openfile<<"&";
        ++it;
    }
    openfile.close();
}

void WordQuery::ReadFromFile(const std::string& path)
{
    ifstream fin(path);
    string buf;
    string content;
    while (getline(fin, buf))
    {
        content.append(buf);
        content.push_back('\n');
    }
    contents_.emplace_back(new u32string(to_utf32(content)));
    string token;
    string KWord;
    int n;
    vector<std::size_t> v;
    int wz;
    char f;
    shared_ptr<std::u32string>p;
    map<std::shared_ptr<Article>, std::vector<std::size_t>>fils;
    content_index_.clear();
    word_search_.clear();
    for(int i=0;i<content.size();i++)
    {
        f=content[i];
        if(f=='~')
        {
            KWord=token;
            token="";
        }
        else if(f=='!')
        {
            n=atoi(token.c_str());
            p=contents_[n];
            content_index_[p]=(size_t)n;
            token="";
        }
        else if(f=='@')
        {
            wz=atoi(token.c_str());
            v.push_back((size_t)wz);
            token="";
        }
        else if(f=='&')
        {
            wz=atoi(token.c_str());
            v.push_back((size_t)wz);
            fils.insert(make_pair(p,v));
            word_search_.insert(make_pair((Word)KWord,fils));
            token="";
            KWord="";
            v.clear();
            fils.clear();

        }
        else if(f=='\n')
        {
            token=token;
        }
        else  
        token+=content[i];

    }
}


std::list<std::shared_ptr<std::u32string>> WordQuery::get_list(const Word& word) const
{
    list<shared_ptr<u32string>> list;
    if (auto it = word_search_.find(word); it != word_search_.end())
    {
        for (const auto& pair: it->second)
        {
            list.push_back(pair.first);
        }
    }
    list.sort();
    return list;
}
