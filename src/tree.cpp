#include"tree.h"
#include"lex.h"
#include"interface.h"
#include"struct_tree.h"

std::string GetSubTrees(ExpNode *node, std::vector<std::string >& v){
    if (node == NULL)
    {
        return "";
    }
    std::string res;
    if (node->left_node != NULL || node->right_node != NULL){
        res = "(";
    }
    res = res + GetSubTrees(node->left_node, v);
    res = res + node->value;
    res = res + GetSubTrees(node->right_node, v);
    if (node->left_node != NULL || node->right_node != NULL){
        res = res + ")";
    }
    v.push_back(res);
    return res;
}
std::vector<std::string> GetAllStdFormulaWithSub(std::string f) {
    
    auto lexer = Lexer();
    auto tokens = lexer.parser(f);
    auto node = GetTree(tokens);
    
    auto res = std::vector<std::string >();
    GetSubTrees(node, res);
    return res;
}