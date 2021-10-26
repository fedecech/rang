#include "Expr.hpp"

/************** BINARY **************/
Expr::Binary::Binary(Expr &left, Token &op, Expr &right) : left_t(left), operator_t(op), right_t(right){};

template <class T>
T Expr::Binary::accept(Visitor<T> visitor) { return visitor.visitBinaryExpr(this); }

/************** GROUPING **************/

Expr::Grouping::Grouping(Expr &expression) : expression_t(expression){};

template <class T>
T Expr::Grouping::accept(Visitor<T> visitor) { return visitor.visitGroupingExpr(this); }

/************** LITERAL **************/
Expr::Literal::Literal(void *value) : value_t(value){};

template <class T>
T Expr::Literal::accept(Visitor<T> visitor) { return visitor.visitLiteralExpr(this); }

/************** UNARY **************/
Expr::Unary::Unary(Token &op, Expr &right) : operator_t(op), right_t(right){};

template <class T>
T Expr::Unary::accept(Visitor<T> visitor) { return visitor.visitUnaryExpr(this); }
