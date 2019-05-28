#ifndef __QUERY_RESULT
#define __QUERY_RESULT

#include <vector>
#include <memory>
#include <string>
#include <cassert>

#include "text.h"

namespace query
{

struct QueryResult
{
    enum class BlockType
    {
        NATURE,
        CONCEPT,
        EXERCISES,
        TEXT,
        EXAMPLE
    };
    QueryResult(const TextBlock& text, const std::vector<std::string>& p_summary, QueryResult::BlockType type)
    {
        id = text.id;
        chapter = text.chapter;
        title = text.title;
        raw = text.raw;
        this->type = type;
        summary = p_summary;
    }

    int id;
    std::string chapter;
    std::string title;
    std::string raw;
    BlockType type;
    std::vector<std::string> summary;
};

} // query

#endif // __QUERY_RESULT