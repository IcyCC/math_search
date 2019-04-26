#ifndef __QUERY_RESULT
#define __QUERY_RESULT

#include <vector>
#include <memory>
#include <string>

namespace query
{

class QueryResult
{
  public:

    QueryResult(const std::shared_ptr<std::u32string>& content,
                std::vector<std::size_t>&& pos)
        : content_(content),
          pos_(std::move(pos))
    {
    }
    


  private:
    std::shared_ptr<std::u32string> content_;
    std::vector<std::size_t> pos_;
    std::vector<std::u32string_view> sentence_;

};

} // query


#endif // __QUERY_RESULT