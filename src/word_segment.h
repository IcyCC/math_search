#ifndef __WORD_SEGMENTER_H
#define __WORD_SEGMENTER_H

#include <map>
#include <memory>
#include <vector>
#include <string>

namespace query
{
// 分词
class WordSegment
{
  public:

    using Word = std::u32string;

    struct WordInfo
    {
        WordInfo() : index(0) { }

        template<typename T>
        WordInfo(T&& w, std::size_t i)
          : word(std::forward<T>(w)), index(i)
        {
        }

        std::u32string word;
        std::size_t index;
        // std::size_t count;
    };

    explicit WordSegment(bool is_article = true) : is_article_(is_article), content_(new std::u32string) { }
    explicit WordSegment(const char* word_freq_file, bool is_article = true);
    // WordSegment(const std::shared_ptr<std::u32string>& content, std::u32string, bool is_article = true);
    WordSegment(const std::shared_ptr<std::u32string>& content,
                std::map<std::u32string, std::u32string::size_type> &&word_count,
                bool is_article = true);
    ~WordSegment() = default;

    void LoadContent(const std::string& file_path);
    void LoadWordCount(const std::string& file_path);
    void SetContent(const std::string& content);
    void SetContent(std::string&& content);
    void SetContent(const std::shared_ptr<std::u32string>& content);
    void SetWordCount(std::map<std::u32string, std::u32string::size_type> &&word_count);
    void SetWordCount(const std::map<std::u32string, std::u32string::size_type>& word_count);

    std::vector<WordInfo> DoSegment(const std::u32string& content, bool is_article) const;

  private:

    struct WordPos
    {
        template<typename T>
        WordPos(T&& w, std::size_t e)
            : word(std::forward<T>(w)), end(e)
        {
        }

        std::u32string word;
        std::size_t end;
    };

    std::vector<WordInfo> DoSegmentImpl(std::u32string_view sentence, size_t article_pos) const;
    std::multimap<std::size_t, WordPos> GetAllWords(std::u32string_view sentence) const;

    bool is_article_;
    std::shared_ptr<std::u32string> content_;
    std::map<std::u32string, size_t> word_count_;
};

} // namespace query

#endif //  __WORD_SEGMENTER_H

