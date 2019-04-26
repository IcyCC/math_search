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
        WordInfo() = default;

        template<typename T>
        WordInfo(T&& w, std::size_t i)
          : word(std::forward<T>(w)), index(i)
        {
        }

        std::u32string word;
        std::size_t index;
        // std::size_t count;
    };

    WordSegment() : content_(new std::u32string) { }
    WordSegment(const char* word_freq_file);
    WordSegment(const std::shared_ptr<std::u32string>& content, std::u32string);
    WordSegment(const std::shared_ptr<std::u32string>& content,
                std::map<std::u32string,
                std::u32string::size_type> &&word_count);
    ~WordSegment() = default;

    void LoadContent(const std::string& file_path);
    void LoadWordCount(const std::string& file_path);
    void SetContent(const std::string& content);
    void SetContent(std::string&& content);
    void SetContent(const std::shared_ptr<std::u32string>& content);
    void SetWordCount(std::map<std::u32string, std::u32string::size_type> &&word_count);
    void SetWordCount(const std::map<std::u32string, std::u32string::size_type>& word_count);

    std::vector<WordInfo> DoSegment() const;

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

    std::shared_ptr<std::u32string> content_;
    std::map<std::u32string, size_t> word_count_;
};

} // namespace query

#endif //  __WORD_SEGMENTER_H

