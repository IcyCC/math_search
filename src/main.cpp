#include "lex.h"
#include "word.h"
#include "tree.h"
#include "util.h"

int main()
{
    std::vector<Token> tokens;
    tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "1"));
    tokens.push_back(Token(TokenType::ADD, TokenMeta::OP, "+"));
    tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "2"));
    tokens.push_back(Token(TokenType::EQ, TokenMeta::OP, "="));
    tokens.push_back(Token(TokenType::VVAR, TokenMeta::VAR, "3"));

    
}