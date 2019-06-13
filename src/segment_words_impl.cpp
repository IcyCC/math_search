#include <vector>
#include <string>

#include "segment.h"
#include "utf.h"

std::vector<std::string> SegmentWordsWithoutStdFormula(const std::string& str)
{
    auto res = query::DefaultSegment(str);
    std::vector<std::string> words;
    for (const auto& elem: res)
    {
        words.push_back(utf::to_utf8(elem.word));
    }
    return words;
}

std::vector<std::string> SegmentWordsWithStdFormula(const std::string& str)
{
    auto res = query::QuerySegment(str);
    std::vector<std::string> words;
    for (const auto& elem: res)
    {
        words.push_back(utf::to_utf8(elem.word));
    }
    return words;
}
