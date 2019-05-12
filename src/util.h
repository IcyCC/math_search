#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

int WriteString2FileAppend(const std::string &file_string, const std::string& str);

int WriteString2File(const std::string &file_string, const std::string& str);

std::string Int2String(int a);

std::vector<std::string> GetAllFilenames(const std::string& dir);

#endif