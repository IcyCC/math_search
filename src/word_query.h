#ifndef __WORD_QUERY_H
#define __WORD_QUERY_H

#include <vector>
#include <string>
#include <list>
#include <memory>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "word_segment.h"
#include "file_path.h"
#include "text.h"
#include "util.h"
//#include "query_result.h"

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
    using QueryResult = std::unordered_map<std::shared_ptr<TextBlock>, std::vector<std::string>>;

    explicit WordQuery(const std::string& dirpath);

    ~WordQuery() = default;
//
    void SaveToFile(const std::string& path) const;
    void ReadFromFile(const std::string& path);
    QueryResult Query(const std::string& sentence) const;

    void LoadContent(const std::string& dirpath);

  private:
    std::list<std::shared_ptr<std::u32string>> get_content_list(const Word &word) const;
    std::list<std::string> get_summary_list(
            const std::vector<WordSegment::WordInfo>& word_infos,
            const std::shared_ptr<std::u32string>&) const;


    std::unordered_map<Article*, std::shared_ptr<TextBlock>> raw_textblock_;
    std::vector<std::shared_ptr<std::u32string>> contents_;

    mutable std::map<std::shared_ptr<std::u32string>, std::size_t> content_index_;
    std::multimap<std::string, std::shared_ptr<TextBlock>> text_block_search_;
    std::map<Word, std::map<std::shared_ptr<Article>, std::vector<std::size_t>>> word_search_;
};

} // namespace query

#endif // __WORD_QUERY_H
