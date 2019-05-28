#pragma once
#include<string>
#include<vector>
#include"query_result.h"

class QueryType
{
   static const int NATURE = 0;
   static const int CONCEPT = 1;
   static const int EXERCISES = 2;
   static const int TEXT = 3;
   static const int EXAMPLE = 4;
};
// 获取公式以及其子公式
std::vector<std::string> GetAllStdFormulaWithSub(std::string f);

// 查询接口
std::vector<query::QueryResult> QueryComm(std::string q, QueryType type);

// 分词
std::vector<std::string> SegmentWords(const std::string& str);

// 标准化公式
std::string StdFormula(std::string f);