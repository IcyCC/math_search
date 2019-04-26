#ifndef __WORD_QUERY_H
#define __WORD_QUERY_H

#include <vector>
#include <string>
#include <list>
#include <memory>
#include <map>
#include <set>
#include <unordered_map>

#include "word_segment.h"
#include "file_path.h"

// #include "query_result.h"

namespace query
{
class WordQuery
{
  public:

    using Word = std::u32string;
    using Article = std::u32string;
    // using QueryResult = std::map<std::shared_ptr<Article>, std::vector<std::size_t>>;
    // using Result = std::map<std::shared_ptr<Article>, std::vector<std::size_t>>;
    // using Content
    using QueryResult = std::unordered_map<std::shared_ptr<std::u32string>, std::unordered_map<
        Word, std::vector<std::u32string_view>>>;

    WordQuery();

    ~WordQuery() = default;

    void SaveToFile(const std::string& path) const;
    QueryResult Query(const std::string& sentence) const;

  private:

    void LoadContent();
    std::list<std::shared_ptr<std::u32string>> get_list(const Word& word) const;

    mutable WordSegment word_segment_;
    std::vector<std::shared_ptr<std::u32string>> contents_;
    mutable std::map<std::shared_ptr<std::u32string>, std::size_t> content_index_;
    std::map<Word, std::map<std::shared_ptr<Article>, std::vector<std::size_t>>> word_search_;
};

} // namespace query

#endif // __WORD_QUERY_H
