#include "util.h"

#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
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


std::vector<std::string > FindAllSub(const std::string& raw,  const std::string& start, const std::string& end) {
    bool is_read = false;
    std::string buffer;
    auto res = std::vector<std::string>();
    for (auto s : raw) {
        buffer.push_back(s);
        if(IsEndWith(buffer, start)) {
            buffer = std::string(start);
            is_read = true;
        }
        if (IsEndWith(buffer, end)) {
            res.push_back(buffer);
            buffer = "";
        }
    }
    return  res;
}