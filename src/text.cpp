#include "text.h"
#include <utility>

std::regex EXERCISES_REGEX = std::regex(R"(\\begin\{exercise\}([\s\S]*?)\\end\{exercise\})");
std::regex NATURE_REGEX = std::regex(R"(\\begin\{propertory\}([\s\S]*?)\\end\{propertory\})");
std::regex CONCEPT_REGEX = std::regex(R"(\\begin\{concept\}([\s\S]*?)\\end\{concept\})");
std::regex EXAMPLE_REGEX = std::regex(R"(\\begin\{example\}([\s\S]*?)\\end\{example\})");
std::regex TEXT_REGEX = std::regex(R"(\\begin\{article\}([\s\S]*?)\\end\{article\})");
//std::regex CHAPTER_BLOCK_REGEX = std::regex(R("subsection\}([\s\S]*/?)end"));//no test
//std::regex TITLE_BLOCK_REGEX = std::regex(R("defintion\}([\s\S]*/?)end"));//no test
//std::regex CHAPTER_REGEX = std::regex(R("subsection\{([\s\S]*/?)\}"));//no test
//std::regex TITLE_REGEX = std::regex(R("defintion\{([\s\S]*/?)\}"));//no test

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

std::vector<std::string> paserLatex2StringCre(yare::Pattern& re, std::string& raw) {
    auto res = re.matches(raw);
    return res;
}


std::vector<TextBlock> ParseFromLatexCRE(std::string filepath) {

    auto  EXERCISES_REGEX_CRE = yare::Pattern(R"(\\begin\{exercise\}([\s\S]*?)\\end\{exercise\})");
    auto NATURE_REGEX_CRE = yare::Pattern(R"(\\begin\{propertory\}([\s\S]*?)\\end\{propertory\})");
    auto CONCEPT_REGEX_CRE = yare::Pattern(R"(\\begin\{concept\}([\s\S]*?)\\end\{concept\})");
    auto  EXAMPLE_REGEX_CRE = yare::Pattern(R"(\\begin\{example\}([\s\S]*?)\\end\{example\})");
    auto  TEXT_REGEX_CRE = yare::Pattern(R"(\\begin\{article\}([\s\S]*?)\\end\{article\})");
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
    auto exercises_strings = paserLatex2StringCre(EXERCISES_REGEX_CRE, raw);
    for (auto &e : exercises_strings){
        res.push_back(std::move(TextBlock(++i,"", "", raw, TextBlock::BlockType::EXERCISES)));
    }

    auto nature_strings = paserLatex2StringCre(NATURE_REGEX_CRE, raw);
    for (auto &e : nature_strings){
        res.push_back(std::move(TextBlock(++i,"", "", raw,  TextBlock::BlockType::NATURE)));
    }

    auto concept_strings = paserLatex2StringCre(CONCEPT_REGEX_CRE, raw);
    for (auto &e : concept_strings){
        res.push_back(std::move(TextBlock(++i,"", "", raw, TextBlock::BlockType::CONCEPT)));
    }


    auto text_strings = paserLatex2StringCre(TEXT_REGEX_CRE, raw);
    for (auto &e : text_strings){
        res.push_back(std::move(TextBlock(++i,"", "", raw,  TextBlock::BlockType::TEXT)));
    }


/*		}

	}
*/

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



