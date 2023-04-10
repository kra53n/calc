#pragma once

#include <string>
#inlcude <fstream>

#include "Token.hpp"

namespace xml {

class Lexer {
private:
  int cur;
  int bol;
  int row;
  std::fstream& const src;
  std::string* cons file_path;
public:
  Lexer(std::string& const _file_path);

  bool is_empty();

  void chop_char();
  void trim_letf();
  Token* next_token();
};

} // xml
