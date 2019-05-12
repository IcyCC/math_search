#include "text.h"

int id=0;
int i=0;

std::regex EXERCISES_REGEX = std::regex(R("exercise\}([\s\S]*/?)end"));
std::regex NATURE_REGEX = std::regex(R("propertory\}([\s\S]*/?)end"));
std::regex CONCEPT_REGEX = std::regex(R("concept\}([\s\S]*/?)end"));
std::regex EXAMPLE_REGEX = std::regex(R("example\}([\s\S]*/?)end"));
std::regex TEXT_REGEX = std::regex(R("article\}([\s\S]*/?)end"));
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
/*  
    auto chapter_strings = paserLatex2String(CHAPTER_REGEX, raw); 
    for (auto x : chapter_strings){
    	
		auto title_strings = paserLatex2String(TITLE_REGEX, raw); 
    	for (auto y : title_strings){
*/    		
			    auto exercises_strings = paserLatex2String(EXERCISES_REGEX, raw);
				for (auto e : exercises_strings){
			        res.push_back(TextBlock(++i, "", raw, TextBlock::BlockType::EXERCISES));
			    } 
			
			    auto nature_strings = paserLatex2String(NATURE_REGEX, raw);
			    for (auto e : nature_strings){
			        res.push_back(TextBlock(++i, "", raw, TextBlock::BlockType::NATURE));
			    } 
			    
			    auto concept_strings = paserLatex2String(CONCEPT_REGEX, raw);
			    for (auto e : concept_strings){
			        res.push_back(TextBlock(++i, "", raw, TextBlock::BlockType::CONCEPT));
			    } 
			
				auto example_strings = paserLatex2String(EXAMPLE_REGEX, raw);
				for (auto e : example_strings){
					res.push_back(TextBlock(++i, "", raw, TextBlock::BlockType::EXAMPLE));
				}
			
			    auto text_strings = paserLatex2String(TEXT_REGEX, raw);
			    for (auto e : text_strings){
			        res.push_back(TextBlock(++i, "", raw, TextBlock::BlockType::TEXT));
			    } 
    		
	
/*		}
    	
	}
*/	
    
    return res;
}
