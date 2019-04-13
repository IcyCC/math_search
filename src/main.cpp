#include<iostream>
#include "lex.h"
#include "word.h"
#include "tree.h"
#include "util.h"
#include"struct_tree.h"

int main()
{
    std::vector<Token> tokens;
    tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "1"));
    tokens.push_back(Token(TokenType::ADD, TokenMeta::OP, "+"));
    tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "2"));
    tokens.push_back(Token(TokenType::EQ, TokenMeta::OP, "="));
    tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "3"));
    tokens.push_back(Token(TokenType::ADD, TokenMeta::OP, "+"));
    tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "0"));

    std::cout<<"TOKENS: "<<std::endl;
    for (auto it = tokens.begin(); it != tokens.end();it++){
        std::cout<< "token: "<< it->value<<std::endl;
    }
    auto node = GetTree(tokens);

    std::cout << OuputTree(node) <<std::endl;
}