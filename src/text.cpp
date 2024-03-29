#include "text.h"
#include "util.h"
#include <utility>
#include <fstream>
#include <iostream>


//std::regex EXERCISES_REGEX = std::regex(R"(\\begin\{exercise\}(.|\\r|\\n)*?end\{exercise\})", std::regex::extended|std::regex::nosubs);
//std::regex NATURE_REGEX = std::regex(R"(\\begin\{propertory\}(.|\\r|\\n)*?end\{propertory\})",std::regex::extended|std::regex::nosubs);
//std::regex CONCEPT_REGEX = std::regex(R"(\\begin\{concept\}(.|\\r|\\n)*?end\{concept\})",std::regex::extended|std::regex::nosubs);
//std::regex EXAMPLE_REGEX = std::regex(R"(\\begin\{example\}(.|\\r|\\n)*?end\{example\})",std::regex::extended|std::regex::nosubs);
//std::regex TEXT_REGEX = std::regex(R"(\\begin\{article\}(.|\\r|\\n)*?end\{article\})",std::regex::extended|std::regex::nosubs);
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
    std::string buf;

    getline(fin, buf);
    id = stoi(buf);
    getline(fin, chapter);
    if (!chapter.empty() && chapter.back() == '\r')
        chapter.pop_back();
    getline(fin, title);
    if (!title.empty() && title.back() == '\r')
        title.pop_back();

    while (getline(fin, buf))
    {
        if (buf.empty())
            continue;
        raw.append(buf);
        raw.push_back('\n');
    }
//    std::cout << "raw:\n" << raw;
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
	
	auto strings = FindAllSub(raw,"\\subsection", "\\subsection",false);
    for (auto &st : strings){
        //cout << "number: ******************************************************" << i  << endl << e << endl;
		//i++;
		int k1=st.find_first_of("{");
		int k2=st.find_first_of("}");
		auto cap=st.substr(k1+1,k2-2);
		std::cout << "**************cap:****************" << cap << std::endl;

//			cout << "******************cap*******************" << st << endl;
		auto defi=FindAllSub(st,"\\definition{","}",false);
		for (auto defi_:defi){
            std::cout << "definition title*******************************************" << defi_ << std::endl;
		}
		
		auto prop=FindAllSub(st,"property{","}",false);
		for (auto prop_:prop){
            std::cout << "property title***********************************************" << prop_ << std::endl;
		}

		int defi_flag = 0;
		int prop_flag = 0;

	     auto exercises_strings = FindAllSub(st,"\\begin{exercise}", "\\end{exercise}", true);
    	 for (auto &e : exercises_strings){
        	 res.push_back(std::move(TextBlock(++i,cap, "", e, TextBlock::BlockType::EXERCISES)));
	     }
 
    	 auto nature_strings = FindAllSub(st,"\\begin{propertory}", "\\end{propertory}", true);
	     for (auto &e : nature_strings){
   	        res.push_back(std::move(TextBlock(++i,cap, prop[prop_flag], e,  TextBlock::BlockType::NATURE)));
             prop_flag++;
	   	  }
 
    	 auto concept_strings = FindAllSub(st,"\\begin{definition}", "\\end{definition}", true);
     	for (auto &e : concept_strings){
        	 res.push_back(std::move(TextBlock(++i,cap,defi[defi_flag], e, TextBlock::BlockType::CONCEPT)));
            defi_flag++;
     	}
 
 
     	auto text_strings = FindAllSub(st,"\\end{document}", "\\end{document}", true);
    	 for (auto &e : text_strings){
        	 res.push_back(std::move(TextBlock(++i,cap, "", e,  TextBlock::BlockType::TEXT)));
     	}
 
   	  auto example_strings = FindAllSub(st,"\\begin{example}", "\\end{example}", true);
    	 for (auto &e : example_strings){
        	 res.push_back(std::move(TextBlock(++i,cap, "", e,  TextBlock::BlockType::EXAMPLE)));
  	   }
		
    }
	/*
	int j=0;
	cout << "******************************************************************************************************************************************************************"<< endl;
	for (auto te : resu){
		cout << "num: " << resu[j].id  << "********" << "***" << resu[j].chapter <<"***"<< resu[j].title << "***"<< resu[j].type <<endl;
	++j;
	}
*/
    return res;
}




