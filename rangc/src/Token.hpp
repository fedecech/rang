#pragma once

#include <iostream>

class Token
{
public:
  enum Type
  {
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    EOF_,
  };

  Token(Type type, std::string lexeme, void *literal, int line);

  Type getType();
  std::string getLexeme();
  void *getLiteral();
  int getLine();
  std::string toString();
  std::string typeToString(Type type);

private:
  Type type_t;
  std::string lexeme_t;
  void *literal_t;
  int line_t;
};
