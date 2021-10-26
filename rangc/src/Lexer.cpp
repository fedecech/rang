#include <iostream>
#include <ctype.h>
#include <map>
#include <stdexcept>

#include "Lexer.hpp"

std::map<std::string, Token::Type> Lexer::keywords = {
    {"and", Token::Type::AND},
    {"class", Token::Type::CLASS},
    {"else", Token::Type::ELSE},
    {"false", Token::Type::FALSE},
    {"for", Token::Type::FOR},
    {"fun", Token::Type::FUN},
    {"if", Token::Type::IF},
    {"or", Token::Type::OR},
    {"print", Token::Type::PRINT},
    {"return", Token::Type::RETURN},
    {"super", Token::Type::SUPER},
    {"this", Token::Type::THIS},
    {"true", Token::Type::TRUE},
    {"const", Token::Type::VAR},
    {"while", Token::Type::WHILE},
};

Lexer::Lexer(const std::string &program) : program_t(program){};

std::vector<Token> Lexer::scan()
{
  while (!this->isEOF())
  {
    this->start_t = this->current_t;
    this->scanToken();
  }

  this->tokens_t.push_back(Token(Token::Type::EOF_, "", nullptr, this->line_t));
  return this->tokens_t;
}

void Lexer::scanToken()
{
  char n = this->next();

  switch (n)
  {
  case '(':
    this->addToken(Token::Type::LEFT_PAREN);
    break;
  case ')':
    this->addToken(Token::Type::RIGHT_PAREN);
    break;
  case '{':
    this->addToken(Token::Type::LEFT_BRACE);
    break;
  case '}':
    this->addToken(Token::Type::RIGHT_BRACE);
    break;
  case ',':
    this->addToken(Token::Type::COMMA);
    break;
  case '.':
    this->addToken(Token::Type::DOT);
    break;
  case '-':
    this->addToken(Token::Type::MINUS);
    break;
  case '+':
    this->addToken(Token::Type::PLUS);
    break;
  case ';':
    this->addToken(Token::Type::SEMICOLON);
    break;
  case '*':
    this->addToken(Token::Type::STAR);
    break;
    // double tokens
  case '!':
    this->addToken(this->match('=') ? Token::Type::BANG_EQUAL : Token::Token::BANG);
    break;
  case '=':
    this->addToken(this->match('=') ? Token::Type::EQUAL_EQUAL : Token::Token::EQUAL);
    break;
  case '<':
    this->addToken(this->match('=') ? Token::Type::LESS_EQUAL : Token::Token::LESS);
    break;
  case '>':
    this->addToken(this->match('=') ? Token::Type::GREATER_EQUAL : Token::Token::GREATER);
    break;
    // ignore tokens
  case '/':
    if (this->match('/'))
      while (this->peek() != '\n' && !this->isEOF())
        this->next();
    else
      this->addToken(Token::Type::SLASH);
    break;
  case '\t':
  case ' ':
  case '\r':
    break;
  case '\n':
    this->line_t++;
    break;
  case '"':
    this->digestString();
    break;
  default:
    if (isdigit(n))
    {
      this->digestNumber();
      break;
    }
    else if (isalpha(n))
    {
      this->digestIndetifier();
      break;
    }
    throw std::runtime_error("Unextected character %s");
    // TODO: Implement lexer error
    // Lexer::error(, f"Unexpected character {c}.");
  }
}

void Lexer::digestIndetifier()
{
  while (isalpha(this->peek()) || isdigit(this->peek()))
    this->next();

  std::string text = this->subProgramAt(this->start_t, this->current_t);
  auto iter = Lexer::keywords.find(text);
  Token::Type type = iter == this->keywords.end() ? Token::Type::IDENTIFIER : iter->second;

  this->addToken(type);
}

void Lexer::digestNumber()
{
  while (isdigit(this->peek()))
    this->next();

  if (this->peek() == '.' || isdigit(this->peekNext()))
  {
    this->next();
    while (isdigit(this->peek()))
      this->next();
  }

  float to_f = std::stof(this->subProgramAt(this->start_t, this->current_t));

  this->addToken(Token::Type::NUMBER, &to_f);
}

void Lexer::digestString()
{
  while (this->peek() != '"' && !this->isEOF())
  {

    if (this->peek() == '\n')
    {
      this->line_t++;
    }
    this->next();
  }

  if (this->isEOF())
  {
    throw std::runtime_error("String literal not ended.");
    return; // Lexer::error()
  }

  this->next();

  std::string value = this->subProgramAt(this->start_t + 1, this->current_t - 1);
  this->addToken(Token::Type::STRING, &value);
}

bool Lexer::match(char expected)
{
  if (this->isEOF())
    return false;

  if (this->program_t.at(this->current_t) != expected)
    return false;

  this->current_t += 1;

  return true;
}

char Lexer::peekNext()
{
  if (this->current_t + 1 >= this->program_t.length())
    return '\0';
  return this->program_t.at(this->current_t + 1);
}

char Lexer::peek()
{
  if (this->isEOF())
    return '\0';
  return this->program_t.at(this->current_t);
}

char Lexer::next()
{
  int tmp = this->current_t;
  this->current_t += 1;
  return this->program_t.at(tmp);
}

bool Lexer::isEOF()
{
  return this->current_t >= this->program_t.length();
}

void Lexer::addToken(Token::Type type, void *literal)
{
  std::string lexeme = this->subProgramAt(this->start_t, this->current_t);
  this->tokens_t.push_back(Token(type, lexeme, literal, this->line_t));
}

void Lexer::addToken(Token::Type type)
{
  std::string lexeme = this->subProgramAt(this->start_t, this->current_t);
  this->tokens_t.push_back(Token(type, lexeme, nullptr, this->line_t));
}

// start included end excluded
std::string Lexer::subProgramAt(const int &start, const int &end)
{
  int length = end - start;
  return this->program_t.substr(start, length);
}