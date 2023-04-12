#pragma once

#include <string>
#include <vector>

#include "Token.hpp"

namespace xml {

class Lexer {
private:
  int cur;
  int bol;
  int row;
  std::string& const src;
  std::vector<Token*>* tokens = nullptr;
public:
  Lexer(std::string& const src);

  bool is_empty();

  void chop_char();
  void trim_left();

  Token* process_double_lexeme();
  Token* process_single_lexeme();
  Token* process_alpha_lexeme();
  
  Token* next_token();
  std::vector<Token*>* lex();
};

} // xml
