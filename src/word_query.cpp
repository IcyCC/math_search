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
    return ch ==' ' || ch == U'。' || ch == U'\r' || ch == U'\n' || ch == 0;
}

// merge two sorted list into lhs
template<typename Elem>
void merge_list(list<Elem>& lhs, const list<Elem>& rhs)
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
            if (word_info.word == U"9015.4")
                std::cout << "Find 9015.4" << std::endl;
//            std::cout << word_info.word << "\n";
            word_search_[word_info.word][content].push_back(word_info.index);
        }
    }
}

void WordQuery::LoadContent(const std::string& dirpath)
{
    for (auto &entry : GetAllFilenames(dirpath))
    {
        auto text_ptr = std::make_shared<TextBlock>(entry);
        auto chapter = text_ptr->chapter;
        if (!chapter.empty() && isdigit(chapter[0]))
        {
            int i = 0;
            while (isdigit(chapter[i]) || chapter[i] == '.' || chapter[i] == ' ')
            {
                ++i;
            }
//            std::cout << "chapter " << std::string(chapter, i, chapter.size() - i) << std::endl;
            text_block_search_.insert({std::string(chapter, i, chapter.size() - i), text_ptr});
        }
        else
        {
//            std::cout << "chapter " << chapter << std::endl;
            text_block_search_.insert({chapter, text_ptr});
        }
        if (!text_ptr->title.empty() && chapter != text_ptr->title)
            text_block_search_.insert({text_ptr->title, text_ptr});
//        std::cout << "title " << text_ptr->title << std::endl;
        auto raw_ptr = new u32string(to_utf32(text_ptr->raw));
        contents_.emplace_back(raw_ptr);
        raw_textblock_.insert({raw_ptr, text_ptr});
    }
}

WordQuery::QueryResult WordQuery::Query(const string& sentence) const
{
    QueryResult result;
    auto word_infos = QuerySegment(sentence);
//    word_infos[0].word = U"9015.4";
    auto it = word_infos.begin();
    list<shared_ptr<u32string>> content_list = get_content_list(it->word);
    for_each(++it, word_infos.end(), [&] (const query::WordSegment::WordInfo& word_info) {
        list<shared_ptr<u32string>> tmp = get_content_list(word_info.word);
        merge_list(content_list, tmp);
    });

    if (content_list.empty())
    {
        goto end;
    }
//    std::cout << sss-- << "\n";
    for (const auto& content_ptr: content_list)
    {
//        std::cout << sss-- << "\n";
        auto summary_list = get_summary_list(word_infos, content_ptr);
        result[raw_textblock_.find(content_ptr.get())->second] =
                vector<std::string>(summary_list.begin(), summary_list.end());
    }
//    std::cout << "Fuck\n";
//    std::cout << result.size() << "\n";

end:
    auto range = text_block_search_.equal_range(sentence);
    for (auto it = range.first; it != range.second; ++it)
    {
        result.insert({it->second, std::vector<std::string>{it->second->raw}});
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
    auto it = word_search_.begin();
    while (it != word_search_.end())
    {
        openfile<<it->first<<"~";
        auto files = (it->second).begin();
        while(files!=(it->second).end())
        {
            openfile<<content_index_[files->first]<<"!";
            for(int i=0;i<files->second.size();i++)
            {
                openfile << files->second[i];
                if (i != (files->second).size()-1)
                    openfile<<"@";
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
    for(char i : content)
    {
        f=i;
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
            word_search_.insert(make_pair(utf::to_utf32(KWord),fils));
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
        token+=i;

    }
}


std::list<std::shared_ptr<std::u32string>> WordQuery::get_content_list(const Word& word) const
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

std::list<std::string> WordQuery::get_summary_list(
        const std::vector<WordSegment::WordInfo>& word_infos,
        const std::shared_ptr<std::u32string> &content_ptr) const
{
    auto kGetList = [&] (const WordSegment::WordInfo& word_info) -> list<std::u32string> {
        list<std::u32string> result;
        set<pair<size_t, size_t>> summaries;
        auto it = word_search_.find(word_info.word);
        assert(it != word_search_.end());
        const auto& map = it->second;

        auto& pos_vec = map.find(content_ptr)->second;
        for (size_t pos: pos_vec)
        {
            auto summary = GetSummary(content_ptr, pos);
            if (auto it = summaries.find(summary); it == summaries.end())
            {
//                auto str = std::u32string(*content_ptr, summary.first, summary.second);
//                std::cout << str << endl;
                result.emplace_back(*content_ptr, summary.first, summary.second);
                summaries.insert(summary);
            }
        }
        result.sort();
        return result;
    };

    auto it = word_infos.begin();
    list<std::u32string> result = kGetList(*it);

    for_each(++it, word_infos.end(), [&] (const WordSegment::WordInfo& word_info) {
        auto tmp = kGetList(word_info);
        merge_list(result, tmp);
    });

    list<std::string> real_result;
    for (const auto& r: result)
        real_result.push_back(utf::to_utf8(r));
    return real_result;
}
