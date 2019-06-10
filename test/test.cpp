#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include<string>
#include <vector>
#include<dirent.h>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include "util.h"


using namespace std;

std::vector<std::string> GetAllFilenames(std::string &inpath);


void File2One(std::string inpath){
	char c[10000];
	ofstream ofile("/Users/suchang/Code/homework/math_search/all.tex");
	vector<string> file=GetAllFilenames(inpath);
	for(auto f: file){
		ifstream ifile(f);
		cout << f << endl;
		while(!ifile.eof()){
			ifile.getline(c,9999);
			ofile << c << endl;
		}
		ifile.close();
	}
	ofile.close();
}





class TextBlock
{
public:

    enum BlockType
    {
        NATURE,
        CONCEPT,
        EXERCISES,
        TEXT,
        EXAMPLE
    };

    int id;
    std::string chapter;
    std::string title;
    std::string raw;
    BlockType type;
    std::string Dumps();
    void Load(const std::string& file_path);

 //   std::vector<KeyWord> depot;    // text keyword gether

    TextBlock(const std::string& path);

    inline TextBlock(int _id, std::string _chapter, std::string _title, std::string _raw, BlockType _type) {
      id = _id;
      chapter = _chapter;
      title = _title;
      raw = _raw;
      type = _type;
};
};

std::string Int2String(int a)
{
    return std::to_string(a);
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



 int WriteString2FileAppend(const std::string &file_string, const std::string    & str);


class AbcStore
{
public:
    std::vector<TextBlock> data;
    virtual int Save(std::string path) = 0;
};

class NatureStore : public AbcStore
{
public:
    int Save(std::string path);
};

class ConceptStore : public AbcStore
{
public:
    int Save(std::string path);
};

class ExercisesStore : public AbcStore
{
public:
    int Save(std::string path);
};

class ExampleStore : public AbcStore
{
public:
    int Save(std::string path);
};

class TextStore : public AbcStore
{
public:
    int Save(std::string path);
};



int NatureStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/nature/" + d.title, d.Dumps());
    }
    return 1;
}

int ConceptStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/concept/" + d.title, d.Dumps());
    }
    return 1;
}

int ExercisesStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/exercises/" + d.title, d.Dumps());
    }
    return 1;
}

int ExampleStore::Save(std::string path)
{
    for (auto d : data){
        WriteString2FileAppend(path + "/example/" + d.title, d.Dumps());
    }
    return 1;
}

int TextStore::Save(std::string path)
{
    for (auto d : data)
    {
        WriteString2FileAppend(path + "/text/" + d.title, d.Dumps());
    }
    return 1;
}


/*
std::vector<std::string> GetAllFilenames(const std::string& dirname)
{
    std::vector<std::string> res;
    DIR* dir;
    struct dirent* dirent;
    if ((dir = ::opendir(dirname.c_str())) == nullptr)
    {
        ::perror("open");
        exit(EXIT_FAILURE);
    }

    while ((dirent = ::readdir(dir)) != nullptr)
    {
        if (strcmp(dirent->d_name, ".") != 0 && strcmp(dirent->d_name, "..") != 0)
            res.emplace_back(dirname + "/" + dirent->d_name);
    }
    ::closedir(dir);
    return res;
}
*/


int WriteString2FileAppend(const std::string &file_string, const std::string& str)
{
    std::ofstream OsWrite(file_string, std::ofstream::app);
    OsWrite << str;
    OsWrite << std::endl;
    return 0;
}


void HandleTex(vector<TextBlock> &vec, std::string outpath){
		vector<TextBlock> nature;
		vector<TextBlock> concept;
		vector<TextBlock> exercise;
		vector<TextBlock> text;
		vector<TextBlock> example;
	
		for(auto v: vec){
			if(v.type==TextBlock::BlockType::NATURE){
				nature.push_back(v);
			}

			else if(v.type==TextBlock::BlockType::CONCEPT){
				concept.push_back(v);
			}

			else if(v.type==TextBlock::BlockType::EXERCISES){
				exercise.push_back(v);
			}

			else if(v.type==TextBlock::BlockType::TEXT){
				text.push_back(v);
			}

			else if(v.type==TextBlock::BlockType::EXAMPLE){
				example.push_back(v);
			}

		}

		
		NatureStore nature_;
		nature_.data=nature;
		nature_.Save(outpath);

		ConceptStore concept_;
		concept_.data=concept;
		concept_.Save(outpath);
	
		ExercisesStore exercise_;
		exercise_.data=exercise;
		exercise_.Save(outpath);		

		TextStore text_;
		text_.data=text;
		text_.Save(outpath);		

		ExampleStore example_;
		example_.data=example;
		example_.Save(outpath);

}

std::vector<std::string> GetAllFilenames(std::string &inpath){
        string temp;
		std::vector<std::string> res;
        temp=(char *)malloc(sizeof(char)*50);
        int j;
        for(int i=6;i<82;i=i+5){
                j=i+5;
                ostringstream ostr;
                ostr << inpath << "/book" << i << "-" << i+4 << ".tex";
                temp=ostr.str();
                //cout << temp << endl;
                //const char *p=temp.data();
				
		res.push_back(temp);

        }
		return res;
}

inline bool IsEndWith(std::string s, std::string m) {
    if (m.length() > s.length()) {
        return false;
    }
    for (int i = 0; i < m.length(); i++) {
        if (m[i] != s[s.length() - m.length() + i]) {
            return false;
        }
    }
    return true;
}

inline bool IsBeginWith(std::string s, std::string m) {
    if (m.length() > s.length()) {
        return false;
    }
    for (int i = 0; i < m.length(); i++) {
        if (m[i] != s[i]) {
            return false;
        }
    }
    return true;
}


std::vector<std::string > FindAllSub(const std::string& raw,  const std::string& start, const std::string& end, bool keep) {
    bool is_read = false;
    std::string buffer;
    auto res = std::vector<std::string>();
    for (int i=0; i<raw.size();i++) {
        auto s = raw[i];
        buffer.push_back(s);
        if (!is_read){
            if(IsEndWith(buffer, start)) {
                if (keep) {
                    buffer = std::string(start);
                } else {
                    buffer = "";
                }
                is_read = true;
            }
        } else {
            if (IsEndWith(buffer, end)) {
                i = i - buffer.size() + 1;
                if (!keep){
                    for(auto &i :end) {
                        buffer.pop_back();
                    }
                }
                res.push_back(buffer);
                buffer = "";
                is_read = false;
            }
        }

    }
    return  res;
}

std::vector<std::string > FindAllCapture(const std::string& raw,  const std::string& start, const std::string& end, bool keep) {
    bool is_read = false;
    std::string buffer;
    auto res = std::vector<std::string>();
    for (auto s : raw) {
        buffer.push_back(s);
        if(IsBeginWith(buffer, start)) {
            if (keep) {
                buffer = std::string(start);
            } else {
                buffer = "";
            }
            is_read = true;
        }
        if (IsBeginWith(buffer, end)) {
            for(auto &i :end) {
                buffer.pop_back();
            }
            res.push_back(buffer);
            buffer = "";
        }
    }
    return  res;
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
    auto exercises_strings = FindAllSub(raw,"\\begin{exercise}", "\\end{exercise}", true);
    for (auto &e : exercises_strings){
        res.push_back(std::move(TextBlock(++i,"", "", e, TextBlock::BlockType::EXERCISES)));
    }

    auto nature_strings = FindAllSub(raw,"\\begin{propertory}", "\\end{propertory}", true);
    for (auto &e : nature_strings){
        res.push_back(std::move(TextBlock(++i,"测试", "测试", e,  TextBlock::BlockType::NATURE)));
    }

    auto concept_strings = FindAllSub(raw,"\\begin{concept}", "\\end{concept}", true);
    for (auto &e : concept_strings){
        res.push_back(std::move(TextBlock(++i,"测试", "测试", e, TextBlock::BlockType::CONCEPT)));
    }


    auto text_strings = FindAllSub(raw,"\\end{document}", "\\end{document}", true);
    for (auto &e : text_strings){
        res.push_back(std::move(TextBlock(++i,"", "", e,  TextBlock::BlockType::TEXT)));
    }

	auto example_strings = FindAllSub(raw,"\\begin{example}", "\\end{example}", true);
    for (auto &e : example_strings){
        res.push_back(std::move(TextBlock(++i,"", "", e,  TextBlock::BlockType::EXAMPLE)));
    }
//

/*		}

	}
*/

    return res;
}



 
void RunSpliteLatex(std::string inpath, std::string outpath){
		DirList(inpath, outpath);
}


/*
std::vector<string> FindAllTitle(std::string str, std::string findstr){
	auto res=std::vector<string> ();
	int count=0;
	int begin=-1;
	while((begin=str.find(findstr,begin+1))!=string::npos) { 
		count++; 
		cout<<begin<<" "<<count<<endl; 

		int k1=str.find("{",begin+1);
		int k2=str.find("}",begin+1);
		auto temp=str.substr(k1+1,k2);
		cout << "**************************************title*********************:"<< temp<<endl;
		res.push_back(temp);

		begin=begin+findstr.length(); 
	}
	return res;
}
*/

int main()
{
		
    auto res = std::vector<string>();
	auto resu = std::vector<TextBlock>();
    std::ifstream infile;
    infile.open("/Users/suchang/Code/homework/math_search/all.tex");
    std::string raw;
    std::string buffer;
    while (std::getline(infile, buffer)) {
        raw = raw + buffer;
	//	cout << buffer << endl;
        raw.push_back('\n');
    }
	int i=0;
    auto strings = FindAllSub(raw,"\\subsection*", "\\subsection", true);
    for (auto &e : strings){
        //cout << "number: ******************************************************" << i  << endl << e << endl;
		//i++;
		int k1=e.find_first_of("{");
		int k2=e.find_first_of("}");
		auto cap=e.substr(k1+1,k2-2);
		cout << "**************cap:****************" << cap << endl;

		auto defi=FindAllSub(e,"\\defination{","}", false);
		for (auto defi_:defi){
			cout << "defination title*******************************************" << defi_ << endl;	
		}
		
		auto prop=FindAllSub(e,"property{","}", false);
		for (auto prop_:prop){
			cout << "property title***********************************************" << prop_ << endl;
		}

	     auto exercises_strings = FindAllSub(e,"\\begin{exercise}", "\\end{exercise}", true);
    	 for (auto &e : exercises_strings){
        	 resu.push_back(std::move(TextBlock(++i,cap, "", e, TextBlock::BlockType::EXERCISES)));
	     }
 
    	 auto nature_strings = FindAllSub(e,"\\begin{propertory}", "\\end{propertory}", true);
	     for (auto &e : nature_strings){
   	      resu.push_back(std::move(TextBlock(++i,cap, "测试", e,  TextBlock::BlockType::NATURE)));
	   	  }
 
    	 auto concept_strings = FindAllSub(e,"\\begin{concept}", "\\end{concept}", true);
     	for (auto &e : concept_strings){
        	 resu.push_back(std::move(TextBlock(++i,cap, "测试", e, TextBlock::BlockType::CONCEPT)));
     	}
 
 
     	auto text_strings = FindAllSub(e,"\\end{document}", "\\end{document}", true);
    	 for (auto &e : text_strings){
        	 resu.push_back(std::move(TextBlock(++i,cap, "", e,  TextBlock::BlockType::TEXT)));
     	}
 
   	  auto example_strings = FindAllSub(e,"\\begin{example}", "\\end{example}", true);
    	 for (auto &e : example_strings){
        	 resu.push_back(std::move(TextBlock(++i,cap, "", e,  TextBlock::BlockType::EXAMPLE)));
  	   }
		
    }
	int j=0;
	cout << "******************************************************************************************************************************************************************"<< endl;
	for (auto te : resu){
		cout << "num: " << resu[j].id  << "********" << "***" << resu[j].chapter <<"***"<< resu[j].title << "***"<< resu[j].type <<endl;
	++j;
	}
 //cout << "***" << resu[3].Dumps()<<endl;
//	  File2One("LaTexDoc");
 //   RunSpliteLatex("LaTexDoc", "text_blocksnew");
    return  0;
}

void DirList(std::string inpath, std::string outpath){
    vector<string> file=GetAllFilenames(inpath);
    auto vec = vector<TextBlock>();
    for(auto f: file){
        vector<TextBlock> t;
        t=ParseFromLatex(f);
        vec.insert(vec.end(), t.begin(), t.end());
    }
    HandleTex(vec, outpath);
}
