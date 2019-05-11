#include"tree.h"
#include"interface.h"

std::vector<std::string> GetAllStdFormulaWithSub(std::string f) {
    
    if (node == NULL)
    {
        return "";
    }
    std::string res;
    if (node->left_node != NULL || node->right_node != NULL){
        res = "(";
    }
    res = res + OuputTree(node->left_node);
    res = res + node->value;
    res = res + OuputTree(node->right_node);
    if (node->left_node != NULL || node->right_node != NULL){
        res = res + ")";
    }
    return res;
}