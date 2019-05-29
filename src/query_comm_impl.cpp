#include <cassert>
#include "interface.h"

#include "query_result.h"
#include "word_segment.h"
#include "word_query.h"

namespace
{
//    NATURE,
//    CONCEPT,
//    EXERCISES,
//    TEXT,
//    EXAMPLE

query::WordQuery concept_query("/Users/suchang/Code/homework/math_search/text_blocks/concept/");
query::WordQuery nature_query("/Users/suchang/Code/homework/math_search/text_blocks/concept/");
query::WordQuery exercises_query("/Users/suchang/Code/homework/math_search/text_blocks/concept/");
query::WordQuery text_query("/Users/suchang/Code/homework/math_search/text_blocks/concept/");
query::WordQuery example_query("/Users/suchang/Code/homework/math_search/text_blocks/concept/");

} // namespace

using namespace query;
using namespace std;

std::vector<query::QueryResult> QueryComm(std::string q, int type)
{
    WordQuery::QueryResult pre_result;
    vector<QueryResult> result;
    switch (type)
    {
        case QueryType::NATURE:
            pre_result = nature_query.Query(q);
            for (const auto& p: pre_result)
            {
                result.emplace_back(*p.first, p.second, QueryResult::BlockType::NATURE);
            }
            break;
        case QueryType::CONCEPT:
            pre_result = concept_query.Query(q);
            for (const auto& p: pre_result)
            {
                result.emplace_back(*p.first, p.second, QueryResult::BlockType::CONCEPT);
            }
            break;
        case QueryType::EXERCISES:
            pre_result = exercises_query.Query(q);
            for (const auto& p: pre_result)
            {
                result.emplace_back(*p.first, p.second, QueryResult::BlockType::EXERCISES);
            }
            break;
        case QueryType::TEXT:
            pre_result = text_query.Query(q);
            for (const auto& p: pre_result)
            {
                result.emplace_back(*p.first, p.second, QueryResult::BlockType::TEXT);
            }
            break;
        case QueryType::EXAMPLE:
            pre_result = example_query.Query(q);
            for (const auto& p: pre_result)
            {
                result.emplace_back(*p.first, p.second, QueryResult::BlockType::EXAMPLE);
            }
            break;
        default:
            assert(0);
    }
    return result;
}