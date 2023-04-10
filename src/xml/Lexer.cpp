#include "Lexer.hpp"
#include "../util.hpp"

namespace xml {

Lexer::Lexer(std::string& const _file_path)
  : file_path(_file_path)
{
  this->src = new std::fstrem(this->file_path, std::fstrem::in);
};

bool Lexer::is_empty() {
  return cur >= file_path->length();
}

void chop_char() {
  if (is_empty()) {
    return;
  }
  cur++;
  if (src[cur-1] == '\n') {
    row++;
    bol = cur;
  }
}

void trim_left() {
  while (not is_empty() and is_skip_char(src[cur])) {
    chop_char();
  }
}

Token::next_token() {
  trim_left();
  while (not is_empty()) {
  }
}

} // xml
