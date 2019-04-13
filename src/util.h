#ifndef UTIL_H
#define UTIL_H
#include <fstream>
#include <iostream>
#include <sstream>

inline int WriteString2FileAppend(const std::string &file_string, const std::string str)
{
    std::ofstream OsWrite(file_string, std::ofstream::app);
    OsWrite << str;
    OsWrite << std::endl;
    OsWrite.close();
    return 0;
}

inline int WriteString2File(const std::string &file_string, const std::string str)
{
    std::ofstream OsWrite(file_string, std::ofstream::app);
    OsWrite << str;
    OsWrite << std::endl;
    OsWrite.close();
    return 0;
}

inline std::string Int2String(int a)
{
    std::string res;
    std::stringstream ss;
    ss << a;
    ss >> res;
    return res;
}

#endif