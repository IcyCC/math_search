#include "text.h"

std::regex EXERCISES_REGEX = std::regex("exercise\}([\s\S]*/?)end");
std::regex NATURE_REGEX = std::regex("propertory\}([\s\S]*/?)end");
std::regex CONCEPT_REGEX = std::regex("concept\}([\s\S]*/?)end");
std::regex TEXT_REGEX = std::regex("article\}([\s\S]*/?)end");


std::string TextBlock::Dumps()
{
    std::string res;
    res = res + Int2String(this->id);
    res = res + "\r\n";
    res = res + this->title;
    res = res + "\r\n";
    res = res + this->raw;
    res = res + "\r\n\r\n";
    return res;
}

std::vector<std::string> paserLatex2String(std::regex re, std::string raw) {
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
    auto res = std::vector<TextBlock>();
    std::ifstream infile;
    infile.open(filepath);
    std::string raw;
    infile >> raw;

    auto exercises_strings = paserLatex2String(EXERCISES_REGEX, raw);
    for (auto e : exercises_strings){
        res.push_back(TextBlock(1, "", raw, TextBlock::BlockType::EXERCISES));
    } 

    auto text_strings = paserLatex2String(TEXT_REGEX, raw);
    for (auto e : text_strings){
        res.push_back(TextBlock(1, "", raw, TextBlock::BlockType::TEXT));
    } 
    
    auto concept_strings = paserLatex2String(CONCEPT_REGEX, raw);
    for (auto e : concept_strings){
        res.push_back(TextBlock(1, "", raw, TextBlock::BlockType::CONCEPT));
    } 

    auto article_strings = paserLatex2String(TEXT_REGEX, raw);
    for (auto e : concept_strings){
        res.push_back(TextBlock(1, "", raw, TextBlock::BlockType::TEXT));
    } 
    
    return res;
}
