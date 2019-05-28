#ifndef __QUERY_RESULT
#define __QUERY_RESULT

#include <vector>
#include <memory>
#include <string>

#include <string>
#include <vector>
#include "text.h"

namespace query
{

struct QueryResult
{
    enum BlockType
    {
        NATURE,
        CONCEPT,
        EXERCISES,
        TEXT,
        EXAMPLE
    };
    int id;
    std::string chapter;
    std::string title;
    std::string raw;
    BlockType type;
    std::vector<std::string> summary;
};

} // query

#endif // __QUERY_RESULT