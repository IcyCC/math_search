#include <vector>
#include <string>

#include "segment.h"
#include "utf.h"

std::vector<std::string> SegmentWords(const std::string& str)
{
    auto res = query::QuerySegment(str);
    std::vector<std::string> words;
    for (const auto& elem: res)
    {
        words.push_back(utf::to_utf8(elem.word));
    }
    return words;
}
