#include <vector>
#include <string>

#include "word_segment.h"
#include "file_path.h"
#include "utf.h"

using namespace std;
using namespace query;

namespace
{
WordSegment segmenter;


int article_segmenter_init = [] () {
    segmenter.LoadWordCount(WORD_FREQ_PATH);
    return 0;
} ();
} // namespace

std::vector<WordSegment::WordInfo> QuerySegment(const std::string& query_str)
{
    return segmenter.DoSegment(utf::to_utf32(query_str), false);
}

std::vector<WordSegment::WordInfo> ArticleSegment(const std::string& article_str)
{
    return segmenter.DoSegment(utf::to_utf32(article_str), true);
}

std::vector<WordSegment::WordInfo> QuerySegment(const std::u32string& query_str)
{
    return segmenter.DoSegment(utf::to_utf32(query_str), false);
}

std::vector<WordSegment::WordInfo> ArticleSegment(const std::u32string& article_str)
{
    return segmenter.DoSegment(utf::to_utf32(article_str), true);
}

std::vector<std::string> SegmentWords(const std::string& str)
{
    auto res = QuerySegment(str);
    std::vector<std::string> words;
    for (const auto& elem: res)
    {
        words.push_back(utf::to_utf8(elem.word));
    }
    return words;
}