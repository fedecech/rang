#include <string>
#include <iostream>

#include "Token.hpp"

#define GET_VARIABLE_NAME(Variable) (#Variable)

Token::Token(Token::Type type, std::string lexeme, void *literal, int line) : type_t(type), lexeme_t(lexeme), literal_t(literal), line_t(line){};

Token::Type Token::getType() { return type_t; }
std::string Token::getLexeme() { return lexeme_t; }
void *Token::getLiteral() { return literal_t; }
int Token::getLine() { return line_t; }
std::string Token::toString() { return "(" + this->typeToString(type_t) + ", " + lexeme_t + ")"; }
std::string Token::typeToString(Token::Type type)
{
    switch (type)
    {
    case Token::Type::LEFT_PAREN:
        return "LEFT_PAREN";
        break;
    case Token::Type::RIGHT_PAREN:
        return "RIGHT_PAREN";
        break;
    case Token::Type::LEFT_BRACE:
        return "LEFT_BRACE";
        break;
    case Token::Type::RIGHT_BRACE:
        return "RIGHT_BRACE";
        break;
    case Token::Type::COMMA:
        return "COMMA";
        break;
    case Token::Type::DOT:
        return "DOT";
        break;
    case Token::Type::SEMICOLON:
        return "SEMICOLON";
        break;
    case Token::Type::PLUS:
        return "PLUS";
        break;
    case Token::Type::MINUS:
        return "MINUS";
        break;
    case Token::Type::SLASH:
        return "SLASH";
        break;
    case Token::Type::STAR:
        return "STAR";
        break;
    case Token::Type::BANG:
        return "BANG";
        break;
    case Token::Type::BANG_EQUAL:
        return "BANG_EQUAL";
        break;
    case Token::Type::EQUAL:
        return "EQUAL";
        break;
    case Token::Type::EQUAL_EQUAL:
        return "EQUAL_EQUAL";
        break;
    case Token::Type::GREATER:
        return "GREATER";
        break;
    case Token::Type::GREATER_EQUAL:
        return "GREATER_EQUAL";
        break;
    case Token::Type::LESS:
        return "LESS";
        break;
    case Token::Type::LESS_EQUAL:
        return "LESS_EQUAL";
        break;
    case Token::Type::IDENTIFIER:
        return "IDENTIFIER";
        break;
    case Token::Type::STRING:
        return "STRING";
        break;
    case Token::Type::NUMBER:
        return "NUMBER";
        break;
    case Token::Type::AND:
        return "AND";
        break;
    case Token::Type::CLASS:
        return "CLASS";
        break;
    case Token::Type::ELSE:
        return "ELSE";
        break;
    case Token::Type::FALSE:
        return "FALSE";
        break;
    case Token::Type::FUN:
        return "FUN";
        break;
    case Token::Type::FOR:
        return "FOR";
        break;
    case Token::Type::IF:
        return "IF";
        break;
    case Token::Type::NIL:
        return "NIL";
        break;
    case Token::Type::OR:
        return "OR";
        break;
    case Token::Type::PRINT:
        return "PRINT";
        break;
    case Token::Type::RETURN:
        return "RETURN";
        break;
    case Token::Type::SUPER:
        return "SUPER";
        break;
    case Token::Type::THIS:
        return "THIS";
        break;
    case Token::Type::TRUE:
        return "TRUE";
        break;
    case Token::Type::VAR:
        return "VAR";
        break;
    case Token::Type::WHILE:
        return "WHILE";
        break;
    case Token::Type::EOF_:
        return "EOF";
        break;
    default:
        break;
    }
}
