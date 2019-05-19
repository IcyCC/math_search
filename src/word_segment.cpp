#include "word_segment.h"

#include <iostream>

#include <unordered_set>
#include <functional>
#include <cassert>
#include <fstream>
#include <memory>
#include <string>
#include <queue>
#include <map>

#include "interface.h"
#include "utf.h"

namespace
{

bool IsDividedChar(char32_t ch)
{
    static const std::unordered_set<char32_t> kDividedChars{
        U'，', U'。', U'：', U'.', U',', U'、', U'？', U'“', U'”', U'\t', U'\n', U' ', U'…', U'(', U')',
        U'（', U'）'};
    return kDividedChars.find(ch) != kDividedChars.end();
}

bool IsAlpha(char32_t ch)
{
    return (ch >= U'a' && ch <= U'z') || (ch >= U'A' && ch <= U'Z');
}

} // namespace

using namespace query;

WordSegment::WordSegment(std::map<std::u32string, std::size_t> &&word_count)
    : word_count_(std::move(word_count))
{
}

WordSegment::WordSegment(const char* word_freq_file)
{
    LoadWordCount(word_freq_file);
}

void WordSegment::LoadWordCount(const std::string& file_path)
{
    std::ifstream fin(file_path);
    std::string word;
    std::size_t count;
    while (fin >> word >> count)
    {
        word_count_.insert({utf::to_utf32(word), count});
    }
    // std::cout << " " << word_count_.size() << std::endl;
}

//void WordSegment::LoadContent(const std::string& file_path)
//{
//    std::ifstream fin(file_path);
//    std::string line;
//    while (std::getline(fin, line))
//    {
//        content_->append(utf::to_utf32(line));
//        content_->push_back(U' ');
//    }
//}
//
//void WordSegment::SetContent(const std::string& content)
//{
//    content_ = std::make_shared<std::u32string>(utf::to_utf32(content));
//}
//
//void WordSegment::SetContent(std::string&& content)
//{
//    content_ = std::make_shared<std::u32string>(utf::to_utf32(content));
//}
//
//void WordSegment::SetContent(const std::shared_ptr<std::u32string>& content)
//{
//    content_ = content;
//}
//
//void WordSegment::SetWordCount(const std::map<std::u32string, std::size_t> &word_count)
//{
//    word_count_ = word_count;
//}
//
//void WordSegment::SetWordCount(std::map<std::u32string, std::size_t> &&word_count)
//{
//    word_count_ = std::move(word_count);
//}

std::vector<WordSegment::WordInfo>
WordSegment::DoSegment(const std::u32string& content, bool is_article) const
{
    std::vector<WordSegment::WordInfo> result;
    size_t begin = 0, i;

    auto add_segments_to_result = [this, &result, &content] (size_t begin, size_t i) {
        auto to_add = this->DoSegmentImpl(std::u32string_view(content.c_str() + begin, i - begin), begin);
        using Iterator = decltype(to_add.begin());
        result.insert(result.end(), std::move_iterator<Iterator>(to_add.begin()),
                      std::move_iterator<Iterator>(to_add.end()));
    };

    for (i = 1; i < content.size(); )
    {
        if (content[i] == U'$')
        {
            size_t start = i;
            do {
                ++i;
            } while (i < content.size() && content[i] != U'$');
            ++i;
            std::u32string formula(content, start, i-start);
            if (is_article)
            {
                auto all_formulas = GetAllStdFormulaWithSub(utf::to_utf8(formula));

                for (const auto& f: all_formulas)
                {
                    result.emplace_back(utf::to_utf32(f), start);
                }
            }
            else
            {
                result.emplace_back(utf::to_utf32(::StdFormula(utf::to_utf8(formula))), start);
            }
            continue;
        }

        // it dependents on that alpha is the same representation in ascii and utf32
        if (IsAlpha(content[i]))
        {
            add_segments_to_result(begin, i);
            begin = i;
            do
            {
                ++i;
            } while (i < content.size() && isalpha(content[i]));
            result.emplace_back(std::u32string(content, begin, i - begin), begin);
            begin = i;
            continue;
        }
        if (IsDividedChar(content[i]))
        {
            add_segments_to_result(begin, i);
            while (i < content.size() && IsDividedChar(content[i]))
                ++i;
            begin = i;
        }
        else
            ++i;
    }

    if (i > begin)
    {
        add_segments_to_result(begin, i);
    }

    return result;
}

std::multimap<std::size_t, WordSegment::WordPos>
WordSegment::GetAllWords(std::u32string_view sentence) const
{
    std::multimap<std::size_t, WordPos> words;
    for (std::size_t i = 0; i < sentence.size(); ++i)
    {
        for (std::size_t j = i + 1; j <= sentence.size(); ++j)
        {
            std::u32string word(sentence.begin() + i, j - i);
            if (auto it = word_count_.find(word); it != word_count_.end())
            {
                words.insert({i, WordPos(std::move(word), j)});
            }
        }
    }
    return words;
}

std::vector<WordSegment::WordInfo>
WordSegment::DoSegmentImpl(std::u32string_view sentence, size_t article_pos) const
{
    using result_t = std::vector<WordSegment::WordInfo>;

    result_t result;
    result_t curr_res;
    std::size_t min_count = 0;

    auto words = GetAllWords(sentence);

    std::function<void(std::size_t, std::size_t)> kDFS = 
        [&] (std::size_t sentence_pos, std::size_t count) {
        if (sentence_pos >= sentence.size())
        {
            if (count > min_count)
            {
                result = curr_res;
                min_count = count;
            }
        }
        if (sentence_pos > sentence.size())
            return;
        auto range = words.equal_range(sentence_pos);
        if (range.first == range.second)
        {
            curr_res.emplace_back(std::u32string(sentence, sentence_pos, 1), article_pos + sentence_pos);
            kDFS(sentence_pos + 1, count);
            curr_res.pop_back();
        }
        else
        {
            for (auto it = range.first; it != range.second; ++it)
            {
                curr_res.emplace_back(it->second.word, article_pos + sentence_pos);
                kDFS(it->second.end, count + word_count_.at(it->second.word));
                curr_res.pop_back();
            }
        }
    };

    kDFS(0, 0);

    return result;
}
