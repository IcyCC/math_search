#pragma once

#include "word.h"
#include<vector>
enum TreeType
{
    UNKNOW,
    PARENT,
    LEFT_NODE,
    RIGHT_NODE
};

inline bool CompareExpNode(ExpNode *a, ExpNode *b)
{   
    if (a == NULL)
    {
        return false;
    }
    if (b == NULL)
    {
        return true;
    }
    return a->value > b->value;
}

inline TreeType GetNodeRelation(ExpNode *r, ExpNode *a)
{
    if (!r) {
        return TreeType::UNKNOW;
    }
    if (r->left_node == a)
    {
        return TreeType::LEFT_NODE;
    }
    else if (r->right_node == a)
    {
        return TreeType::RIGHT_NODE;
    }
    else if (r->parent_node == a)
    {
        return TreeType::PARENT;
    }
    else
    {
        return TreeType::UNKNOW;
    }
}

inline bool SwapTreeNode(ExpNode* root, ExpNode *l, ExpNode *r)
{   
     root->left_node = r;
     root->right_node =  l;
    return true;
}

inline void StdTree(ExpNode *node)
{
    if(node == NULL){
        return;
    }
    // 按大于标准化树
    if(node->token!=NULL&&node->token->type!=TokenType::DIV &&node->token->type!=TokenType::SUB )
    if (!CompareExpNode(node->left_node, node->right_node))
    {
        SwapTreeNode(node, node->left_node, node->right_node);
    }

    if(node->token == NULL){
        if (!CompareExpNode(node->left_node, node->right_node))
        {
            SwapTreeNode(node, node->left_node, node->right_node);
        }
    }
    StdTree(node->left_node);
    StdTree(node->right_node);
}



inline std::string OuputTree(ExpNode *node)
{
    if (node == NULL)
    {
        return "";
    }
    std::string res;
    if (node->left_node != NULL || node->right_node != NULL){
//        res = "(";
    }
    res = res + OuputTree(node->left_node);
    res = res + node->value;
    res = res + OuputTree(node->right_node);
    if (node->left_node != NULL || node->right_node != NULL){
//        res = res + ")";
    }
    return res;
}

std::string GetSubTrees(ExpNode *node, std::vector<std::string >& v);