#include "word_query.h"

// #include <filesystem>
#include <algorithm>
#include <list>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <cassert>
#include <map>

#include "word_segment.h"
#include "utf.h"
#include "file_path.h"

using namespace query;
using namespace std;
using namespace utf;

// namespace fs = std::filesystem;

namespace
{

bool IsDelimiter(char32_t ch)
{
    if (ch == U'.' || ch == U'。' || ch == U'\r' || ch == U'\n' || ch == 0)
        return true;
    else
        return false;
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

WordQuery::WordQuery()
    : word_segment_(WORD_FREQ_PATH)
{
    LoadContent();

    // for every content
    for (const auto &content : contents_)
    {
        word_segment_.SetContent(content);
        auto word_infos = word_segment_.DoSegment();
        for (const auto &word_info : word_infos)
        {
            word_search_[word_info.word][content].push_back(word_info.index);
        }
    }
}

void WordQuery::LoadContent()
{
    // for (auto &entry : fs::directory_iterator(CONTENT_DIR_PATH))
    // {
    //     ifstream fin(entry.path());
    //     string buf;
    //     string content;
    //     while (getline(fin, buf))
    //     {
    //         content.append(buf);
    //         content.push_back('\n');
    //     }
    //     contents_.emplace_back(new u32string(to_utf32(content)));
    // }
}

WordQuery::QueryResult WordQuery::Query(const string& sentence) const
{
    word_segment_.SetContent(sentence);
    auto word_infos = word_segment_.DoSegment();
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
                    result[content][word_info.word].emplace_back(content->c_str() + pair.first, pair.second);
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

    // TODO: save to file
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
