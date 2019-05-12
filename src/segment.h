#ifndef __SEGMENT_H
#define __SEGMENT_H

#include <string>
#include <vector>
#include "word_segment.h"

namespace query
{
std::vector<WordSegment::WordInfo> ArticleSegment(const std::string& article_str);
std::vector<WordSegment::WordInfo> QuerySegment(const std::string& query_str);
std::vector<WordSegment::WordInfo> ArticleSegment(const std::u32string& article_str);
std::vector<WordSegment::WordInfo> QuerySegment(const std::u32string& query_str);
} // namespace query

#endif //MATH_SEARCH_SEGMENT_H
