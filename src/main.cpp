#include<iostream>
#include "lex.h"
#include "word.h"
#include "tree.h"
#include "util.h"
#include "text.h"
#include"struct_tree.h"

int main()
{
    // std::vector<Token> tokens;
    // tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "1"));
    // tokens.push_back(Token(TokenType::ADD, TokenMeta::OP, "+"));
    // tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "2"));
    // tokens.push_back(Token(TokenType::EQ, TokenMeta::OP, "="));
    // tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "3"));
    // tokens.push_back(Token(TokenType::ADD, TokenMeta::OP, "+"));
    // tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "0"));


    // std::cout<<"TOKENS: "<<std::endl;
    // for (auto it = tokens.begin(); it != tokens.end();it++){
    //     std::cout<< "token: "<< it->value<<std::endl;
    // }
    // auto node = GetTree(tokens);
    // // StdTree(node);
    // std::cout << OuputTree(node) <<std::endl;
    
    auto blocks1 = ParseFromLatex("/Users/suchang/Code/homework/math_search/LaTexDoc/book31-35.tex");
    for (auto b : blocks1){
        std::cout<<b.Dumps()<<std::endl; 
    }

    auto blocks2 = ParseFromLatex("/Users/suchang/Code/homework/math_search/LaTexDoc/book86-90.tex");
    for (auto b : blocks2){
        std::cout<<b.Dumps()<<std::endl; 
    }
}