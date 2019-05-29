#include "util.h"

#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <ostream>
#include <iostream>
#include <cstring>


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

std::vector<std::string> GetAllFilenamesZZZ(std::string &inpath){
        std::string temp;
		std::vector<std::string> res;
        temp=(char *)malloc(sizeof(char)*50);
        int j;
        for(int i=6;i<82;i=i+5){
                j=i+5;
                std::ostringstream ostr;
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

void File2One(std::string inpath){
    char c[10000];
    std::ofstream ofile("all.tex");
    std::vector<std::string> file=GetAllFilenamesZZZ(inpath);
    for(auto f: file){
        std::ifstream ifile(f);
        std::cout << f << std::endl;
        while(!ifile.eof()){
            ifile.getline(c,9999);
            ofile << c << std::endl;
        }
        ifile.close();
    }
    ofile.close();
}
