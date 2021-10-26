#include "Parser.hpp"

Parser::Parser(const std::vector<Token> &tokens) : tokens_t(tokens){};

Expr Parser::parse()
{
  try
  {
    return this->expression();
  }
  catch (std::exception)
  {
    std::cout << "ERROR" << std::endl;
  }
}

void Parser::syncronize()
{
  this->next();

  while (!this->isEOF())
  {
    if (this->previous().getType() == Token::Type::SEMICOLON)
      return;

    Token::Type pt = this->peek().getType();
    switch (pt)
    {
    case Token::Type::CLASS:
    case Token::Type::FUN:
    case Token::Type::VAR:
    case Token::Type::FOR:
    case Token::Type::IF:
    case Token::Type::WHILE:
    case Token::Type::PRINT:
    case Token::Type::RETURN:
      break;
    default:
      this->next();
      break;
    }
  }
}

Expr Parser::expression() { return this->equality(); }

Expr Parser::equality()
{
  Expr expr = this->comparison();

  while (this->match({Token::Type::BANG_EQUAL, Token::Type::EQUAL_EQUAL}))
  {
    Token op = this->previous();
    Expr right = this->comparison();
    expr = Expr::Binary(expr, op, right);
  }

  return expr;
}

Expr Parser::comparison()
{
  Expr expr = this->term();

  while (this->match({Token::Type::GREATER, Token::Type::GREATER_EQUAL, Token::Type::LESS, Token::Type::LESS_EQUAL}))
  {
    Token op = this->previous();
    Expr right = this->term();
    expr = Expr::Binary(expr, op, right);
  }

  return expr;
}

Expr Parser::term()
{
  Expr expr = this->factor();

  while (this->match({Token::Type::MINUS, Token::Type::PLUS}))
  {
    Token op = this->previous();
    Expr right = this->factor();
    expr = Expr::Binary(expr, op, right);
  }

  return expr;
}

Expr Parser::factor()
{
  Expr expr = this->unary();

  while (this->match({Token::Type::SLASH, Token::Type::STAR}))
  {
    Token op = this->previous();
    Expr right = this->unary();
    expr = Expr::Binary(expr, op, right);
  }

  return expr;
}

Expr Parser::unary()
{
  if (this->match({Token::Type::BANG, Token::Type::MINUS}))
  {
    Token op = this->previous();
    Expr right = this->unary();
    return Expr::Unary(op, right);
  }

  return this->primary();
}

Expr Parser::primary()
{
  if (this->match({Token::Type::FALSE}))
    return Expr::Literal((void *)"false");
  if (this->match({Token::Type::TRUE}))
    return Expr::Literal((void *)"true");

  if (this->match({Token::Type::NUMBER, Token::Type::STRING}))
    return Expr::Literal(this->previous().getLiteral());

  if (this->match({Token::Type::LEFT_PAREN}))
  {
    Expr expr = this->expression();
    this->consume(Token::Type::RIGHT_PAREN, "Expect ')' after expression.");
    return Expr::Grouping(expr);
  }

  std::cout << "ERROR: not impelemented yet" << std::endl;
}

Token Parser::consume(const Token::Type &type, const std::string &msg)
{
  if (this->check(type))
    return this->next();

  std::cout << "ERROR: not impelemented yet" << std::endl;
}

void Parser::error(const Token::Type &type, const std::string &msg)
{
  std::cout << "ERROR: not impelemented yet" << std::endl;
  return;
}

bool Parser::match(const std::vector<Token::Type> &types)
{
  for (Token::Type t : types)
    if (this->check(t))
    {
      this->next();
      return true;
    }

  return false;
}

bool Parser::check(const Token::Type &type)
{
  if (this->isEOF())
    return false;

  return this->peek().getType() == type;
}

Token Parser::peek()
{
  return this->tokens_t.at(this->current_t);
}

Token Parser::previous()
{
  return this->tokens_t.at(this->current_t - 1);
}

Token Parser::next()
{
  if (!this->isEOF())
    this->current_t++;
  return this->previous();
}

bool Parser::isEOF()
{
  return this->peek().getType() == Token::Type::EOF_;
}
