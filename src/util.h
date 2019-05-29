#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>


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
std::vector<std::string> GetAllFilenames(const std::string& dir);


std::vector<std::string> GetAllFilenamesZZZ(const std::string& dir);

int WriteString2FileAppend(const std::string &file_string, const std::string& str);

int WriteString2File(const std::string &file_string, const std::string& str);

std::string Int2String(int a);


std::vector<std::string > FindAllSub(const std::string& raw,const std::string& start, const std::string &end, bool keep);

void File2One(std::string inpath);

#endif
