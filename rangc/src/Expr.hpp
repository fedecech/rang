#pragma once

#include "Token.hpp"

class Expr
{
public:
  class Binary;
  class Grouping;
  class Literal;
  class Unary;

  template <class T>
  class Visitor;

  template <class T>
  T accept(Visitor<T> visitor);
};

static class Expr::Binary : public Expr
{
public:
  Binary(Expr &left, Token &op, Expr &right);

  template <class T>
  T accept(Visitor<T> visitor);

private:
  const Expr left_t;
  const Token operator_t;
  const Expr right_t;
};

static class Expr::Grouping : public Expr
{
public:
  Grouping(Expr &expression);

  template <class T>
  T accept(Visitor<T> visitor);

private:
  const Expr expression_t;
};

static class Expr::Literal : public Expr
{
public:
  Literal(void *value);

  template <class T>
  T accept(Visitor<T> visitor);

private:
  const void *value_t;
};

static class Expr::Unary : public Expr
{
public:
  Unary(Token &op, Expr &right);

  template <class T>
  T accept(Visitor<T> visitor);

private:
  const Token operator_t;
  const Expr right_t;
};

template <class T>
class Expr::Visitor
{
  virtual T visitBinaryexpr(Expr::Binary expr);
  virtual T visitGroupingExpr(Expr::Grouping expr);
  virtual T visitLiteralExpr(Expr::Literal expr);
  virtual T visitUnaryExpr(Expr::Unary expr);
};