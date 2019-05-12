#pragma once
#include<string>
#include<vector>
#include"query_result.h"

enum QueryType {

};

// 获取公式以及其子公式
std::vector<std::string> GetAllStdFormulaWithSub(std::string f);

// 查询接口
std::vector<query::QueryResult> QueryComm(std::string q, QueryType type);

// 分词
std::vector<std::string> SegmentWords(const std::string& str);
