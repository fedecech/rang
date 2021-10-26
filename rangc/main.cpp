#include <iostream>
#include <fstream>
#include <streambuf>
#include <vector>
#include <string>

#include "./src/Lexer.hpp"
#include "./src/Token.hpp"

int main()
{
  std::ifstream t("sample.rg");
  std::string program((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());

  Lexer lex(program);
  std::vector<Token> tokens = lex.scan();

  for (Token t : tokens)
    std::cout << t.toString() << std::endl;
  return 0;
}
