#include "text.h"

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

std::vector<TextBlock> ParseFromLatex(std::string filepath)
{
    std::ifstream infile;
    infile.open(filepath);
    std::string raw;
    infile >> raw;

    std::regex pattern_exercise("\\begin\{exercise\}([\s\S]*?)\\end\{exercise\}", std::regex::icase);
    std::regex pattern_exercise("\\begin\{Nature\}([\s\S]*?)\\end\{exercise\}", std::regex::icase);
}
