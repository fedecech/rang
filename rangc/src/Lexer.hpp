#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Token.hpp"

class Lexer
{
public:
  Lexer(const std::string &program);

  std::vector<Token> scan();
  static void error(Token token, std::string msg);

private:
  void scanToken();
  void digestIndetifier();
  void digestString();
  void digestNumber();
  bool match(char expected);
  char peekNext();
  char peek();
  char next();
  bool isEOF();
  void addToken(Token::Type type, void *literal);
  void addToken(Token::Type type);
  std::string subProgramAt(const int &start, const int &end);

  std::string program_t;
  std::vector<Token> tokens_t;
  int line_t = 1;
  int current_t = 0;
  int start_t = 0;
  static std::map<std::string, Token::Type> keywords;
};
