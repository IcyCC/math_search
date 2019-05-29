#include "util.h"

#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>

void File2One(std::string inpath){
	char c[10000];
	ofstream ofile("all.tex");
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

int WriteString2FileAppend(const std::string &file_string, const std::string& str)
{
    std::ofstream OsWrite(file_string, std::ofstream::app);
    OsWrite << str;
    OsWrite << std::endl;
    return 0;
}

int WriteString2File(const std::string &file_string, const std::string& str)
{
    std::ofstream OsWrite(file_string);
    OsWrite << str;
    OsWrite << std::endl;
    return 0;
}

std::string Int2String(int a)
{
    return std::to_string(a);
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
