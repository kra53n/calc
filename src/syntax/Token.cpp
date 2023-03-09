#include "Token.hpp"

int Token::priority(Token& tk) {
  return _token_priority.find(this->name)->second - _token_priority.find(tk.name)->second;
}
