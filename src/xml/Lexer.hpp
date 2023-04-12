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

  bool _is_empty();
  bool _is_part_of_plural_lexeme();

  void _chop_char();
  void _trim_left();

  Token* _process_double_lexeme();
  Token* _process_single_lexeme();
  Token* _process_plural_lexeme();
  
  Token* next_token();
public:
  Lexer(std::string& const src);
  std::vector<Token*>* lex();
};

} // xml
