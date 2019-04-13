#pragma once

#include "word.h"

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

inline bool SwapTreeNode(ExpNode *a, ExpNode *b)
{
    TreeType a_type = GetNodeRelation(a->parent_node, a);
    TreeType b_type = GetNodeRelation(b->parent_node, b);
    if (a_type == TreeType::LEFT_NODE && b_type == TreeType::LEFT_NODE)
    {
        a->parent_node->left_node = b;
        b->parent_node->left_node = a;
        ExpNode *p = a->parent_node;
        a->parent_node = b->parent_node;
        return true;
    }
    else if (a_type == TreeType::LEFT_NODE && b_type == TreeType::RIGHT_NODE)
    {
        a->parent_node->left_node = b;
        b->parent_node->right_node = a;
        ExpNode *p = a->parent_node;
        a->parent_node = b->parent_node;
        return true;
    }
    else if (a_type == TreeType::RIGHT_NODE && b_type == TreeType::LEFT_NODE)
    {
        a->parent_node->right_node = b;
        b->parent_node->left_node = a;
        ExpNode *p = a->parent_node;
        a->parent_node = b->parent_node;
        return true;
    }
    else if (a_type == TreeType::RIGHT_NODE && b_type == TreeType::RIGHT_NODE)
    {
        a->parent_node->right_node = b;
        b->parent_node->right_node = a;
        ExpNode *p = a->parent_node;
        a->parent_node = b->parent_node;
        return true;
    }
    else
    {
        return false;
    }
}

inline void StdTree(ExpNode *node)
{
    // 按大于标准化树
    if (!CompareExpNode(node->left_node, node->right_node))
    {
        SwapTreeNode(node->left_node, node->right_node);
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
    res = res + OuputTree(node->left_node);
    res = res + node->value;
    res = res + OuputTree(node->right_node);
    return res;
}