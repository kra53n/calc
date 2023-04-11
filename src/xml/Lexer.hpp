#pragma once

#include <string>
#include <vector>
#include <fstream>

#include "Token.hpp"

namespace xml {

class Lexer {
private:
  int cur;
  int bol;
  int row;
  std::fstream& const src;
  std::string* const file_path = nullptr;
  std::vector<Token*>* tokens = nullptr;
public:
  Lexer(std::string& const _file_path);

  bool is_empty();

  void chop_char();
  void trim_letf();

  Token* process_double_lexeme();
  Token* process_single_lexeme();
  
  Token* next_token();
  std::vector<Token*>* lex();
};

} // xml
