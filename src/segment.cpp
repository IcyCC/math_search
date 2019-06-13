#include <vector>
#include <string>

#include "word_segment.h"
#include "file_path.h"
#include "utf.h"

using namespace std;
using namespace query;

namespace
{
WordSegment& GetWordSegment()
{
    static WordSegment segmenter(WORD_FREQ_PATH);
    return segmenter;
}
} // namespace

namespace query
{
std::vector<WordSegment::WordInfo> DefaultSegment(const std::string &query_str)
{
    return GetWordSegment().DoSegment(utf::to_utf32(query_str), WithoutFormula);
}

std::vector<WordSegment::WordInfo> DefaultSegment(const std::u32string &query_str)
{
    return GetWordSegment().DoSegment(query_str, WithoutFormula);
}

std::vector<WordSegment::WordInfo> QuerySegment(const std::string &query_str)
{
    return GetWordSegment().DoSegment(utf::to_utf32(query_str), StdFormula);
}

std::vector<WordSegment::WordInfo> ArticleSegment(const std::string &article_str)
{
    return GetWordSegment().DoSegment(utf::to_utf32(article_str), AllFormula);
}

std::vector<WordSegment::WordInfo> QuerySegment(const std::u32string &query_str)
{
    return GetWordSegment().DoSegment(query_str, StdFormula);
}

std::vector<WordSegment::WordInfo> ArticleSegment(const std::u32string &article_str)
{
    return GetWordSegment().DoSegment(article_str, AllFormula);
}
} // namespace query
