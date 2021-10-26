#pragma once

#include <vector>

#include "Token.hpp"
#include "Expr.hpp"
#include "Lexer.hpp"

class Parser
{
public:
  Parser(const std::vector<Token> &tokens);

  Expr parse();

private:
  void syncronize();
  Expr expression();
  Expr equality();
  Expr comparison();
  Expr term();
  Expr factor();
  Expr unary();
  Expr primary();
  Token consume(const Token::Type &type, const std::string &msg);
  void error(const Token::Type &type, const std::string &msg);
  bool match(const std::vector<Token::Type> &types);
  bool check(const Token::Type &type);
  Token peek();
  Token previous();
  Token next();
  bool isEOF();

  int current_t = 0;
  const std::vector<Token> tokens_t;
};
