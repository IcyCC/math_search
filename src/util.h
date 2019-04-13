#pragma once
#include <fstream>
#include <iostream>
#include <sstream>

int WriteString2FileAppend(const std::string &file_string, const std::string str)
{
    std::ofstream OsWrite(file_string, std::ofstream::app);
    OsWrite << str;
    OsWrite << std::endl;
    OsWrite.close();
    return 0;
}

int WriteString2File(const std::string &file_string, const std::string str)
{
    std::ofstream OsWrite(file_string, std::ofstream::app);
    OsWrite << str;
    OsWrite << std::endl;
    OsWrite.close();
    return 0;
}

std::string Int2String(int a)
{
    std::string res;
    std::stringstream ss;
    ss << a;
    ss >> res;
    return res;
}