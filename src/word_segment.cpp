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
        U'（', U'）', U'{', U'}'};
    return kDividedChars.find(ch) != kDividedChars.end();
}

bool IsAlphaOrDigit(char32_t ch)
{
    return (ch >= U'a' && ch <= U'z') || (ch >= U'A' && ch <= U'Z')
        || (ch >= U'0' && ch <= U'9');
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

    for (i = 0; i < content.size(); )
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
        if (IsAlphaOrDigit(content[i]))
        {
            AddSegmentsToResult(result, content, begin, i);
            begin = i;
            do
            {
                ++i;
            } while (i < content.size() && IsAlphaOrDigit(content[i]));
            result.emplace_back(std::u32string(content, begin, i - begin), begin);
            begin = i;
            continue;
        }
        if (IsDividedChar(content[i]))
        {
            AddSegmentsToResult(result, content, begin, i);
            while (i < content.size() && IsDividedChar(content[i]))
                ++i;
            begin = i;
        }
        else
            ++i;
    }

    if (i > begin)
    {
        AddSegmentsToResult(result, content, begin, i);
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

    DoSegImplDfs(0, 0, article_pos, min_count, sentence, result, curr_res, words);

    return result;
}

void WordSegment::AddSegmentsToResult(std::vector<WordSegment::WordInfo>& result,
                         const std::u32string& content,
                         size_t begin, size_t i) const
{
    auto to_add = DoSegmentImpl(std::u32string_view(content.c_str() + begin, i - begin), begin);
    using Iterator = decltype(to_add.begin());
    result.insert(result.end(), std::move_iterator<Iterator>(to_add.begin()),
                  std::move_iterator<Iterator>(to_add.end()));
//    for (const auto& word: result) {
//        std::cout << "f " << word.word << std::endl;
//    }
}

void WordSegment::DoSegImplDfs(std::size_t sentence_pos,
                               std::size_t count,
                               std::size_t article_pos,
                               std::size_t& min_count,
                               std::u32string_view sentence,
                               std::vector<WordSegment::WordInfo>& result,
                               std::vector<WordSegment::WordInfo>& curr_res,
                               const std::multimap<std::size_t, WordSegment::WordPos>& words) const
{
    if (sentence_pos >= sentence.size())
    {
        if (count > min_count)
        {
            result = curr_res;
            min_count = count;
        }
        return;
    }
    auto range = words.equal_range(sentence_pos);
    if (range.first == range.second)
    {
//        std::cout << std::u32string(sentence, sentence_pos, 1) << "\n";
        curr_res.emplace_back(std::u32string(sentence, sentence_pos, 1), article_pos + sentence_pos);
        DoSegImplDfs(sentence_pos + 1, count, article_pos, min_count, sentence, result, curr_res, words);
        if (!curr_res.empty())
            curr_res.pop_back();
    }
    else
    {
        for (auto it = range.first; it != range.second; ++it)
        {
//            std::cout << "a " << WordSegment::WordInfo(it->second.word, article_pos + sentence_pos).word << "\n";
            curr_res.emplace_back(it->second.word, article_pos + sentence_pos);
            DoSegImplDfs(it->second.end, count + word_count_.at(it->second.word), article_pos, min_count, sentence, result, curr_res, words);
            if (!curr_res.empty())
                curr_res.pop_back();
        }
    }
}
