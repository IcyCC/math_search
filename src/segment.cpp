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


auto article_segmenter_init = [] () {
    segmenter.LoadWordCount(WORD_FREQ_PATH);
    return 0;
} ();
} // namespace

namespace query
{
std::vector<WordSegment::WordInfo> QuerySegment(const std::string &query_str)
{
    return segmenter.DoSegment(utf::to_utf32(query_str), false);
}

std::vector<WordSegment::WordInfo> ArticleSegment(const std::string &article_str)
{
    return segmenter.DoSegment(utf::to_utf32(article_str), true);
}

std::vector<WordSegment::WordInfo> QuerySegment(const std::u32string &query_str)
{
    return segmenter.DoSegment(query_str, false);
}

std::vector<WordSegment::WordInfo> ArticleSegment(const std::u32string &article_str)
{
    return segmenter.DoSegment(article_str, true);
}
} // namespace query
