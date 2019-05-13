#include "text.h"
#include <utility>
#include <fstream>

std::regex EXERCISES_REGEX = std::regex(R"(\\begin\{exercise\}(.|\\r|\\n)*?end\{exercise\})", std::regex::extended|std::regex::nosubs);
std::regex NATURE_REGEX = std::regex(R"(\\begin\{propertory\}(.|\\r|\\n)*?end\{propertory\})",std::regex::extended|std::regex::nosubs);
std::regex CONCEPT_REGEX = std::regex(R"(\\begin\{concept\}(.|\\r|\\n)*?end\{concept\})",std::regex::extended|std::regex::nosubs);
std::regex EXAMPLE_REGEX = std::regex(R"(\\begin\{example\}(.|\\r|\\n)*?end\{example\})",std::regex::extended|std::regex::nosubs);
std::regex TEXT_REGEX = std::regex(R"(\\begin\{article\}(.|\\r|\\n)*?end\{article\})",std::regex::extended|std::regex::nosubs);
//std::regex CHAPTER_BLOCK_REGEX = std::regex(R("subsection\}([\s\S]*/?)end"));//no test
//std::regex TITLE_BLOCK_REGEX = std::regex(R("defintion\}([\s\S]*/?)end"));//no test
//std::regex CHAPTER_REGEX = std::regex(R("subsection\{([\s\S]*/?)\}"));//no test
//std::regex TITLE_REGEX = std::regex(R("defintion\{([\s\S]*/?)\}"));//no test

TextBlock::TextBlock(const std::string& path)
{
    Load(path);
}

std::string TextBlock::Dumps()
{
    std::string res;
    res = res + Int2String(this->id);
    res = res + "\r\n";
    res = res + this->chapter;
    res = res + "\r\n";
    res = res + this->title;
    res = res + "\r\n";
    res = res + this->raw;
    res = res + "\r\n\r\n";
    return res;
}

void TextBlock::Load(const std::string &file_path)
{
    std::ifstream fin(file_path);
    fin >> id;
    fin >> chapter;
    fin >> title;
    std::string buf;
    while (getline(fin, buf))
    {
        raw.append(buf);
        raw.push_back('\n');
    }
}

std::vector<std::string> paserLatex2String(std::regex& re, std::string& raw) {
    auto res = std::vector<std::string>();
    auto words_begin =
            std::sregex_iterator(raw.begin(), raw.end(), re);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        res.push_back(match_str);
    }
    return res;
}




std::vector<TextBlock> ParseFromLatex(std::string filepath)
{
    int i = 0;
    auto res = std::vector<TextBlock>();
    std::ifstream infile;
    infile.open(filepath);
    std::string raw;
    std::string buffer;
    while (std::getline(infile, buffer)) {
        raw = raw + buffer;
        raw.push_back('\n');
    }
    auto exercises_strings = paserLatex2String(EXERCISES_REGEX, raw);
    for (auto &e : exercises_strings){
        res.push_back(std::move(TextBlock(++i,"", "", raw, TextBlock::BlockType::EXERCISES)));
    }

    auto nature_strings = paserLatex2String(NATURE_REGEX, raw);
    for (auto &e : nature_strings){
        res.push_back(std::move(TextBlock(++i,"", "", raw,  TextBlock::BlockType::NATURE)));
    }

    auto concept_strings = paserLatex2String(CONCEPT_REGEX, raw);
    for (auto &e : concept_strings){
        res.push_back(std::move(TextBlock(++i,"", "", raw, TextBlock::BlockType::CONCEPT)));
    }


    auto text_strings = paserLatex2String(TEXT_REGEX, raw);
    for (auto &e : text_strings){
        res.push_back(std::move(TextBlock(++i,"", "", raw,  TextBlock::BlockType::TEXT)));
    }


/*		}

	}
*/

    return res;
}



