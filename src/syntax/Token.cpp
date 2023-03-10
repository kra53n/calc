#include "Token.hpp"

int Token::priority(Token& tk) {
  return _token_priority.find(this->name)->second - _token_priority.find(tk.name)->second;
}

std::ostream& operator<<(std::ostream& out, const Token& token) {
  out << "Text: " << token.text << "; ";
  out << "Start pos: " << token.start_pos << "; ";
  out << "End pos: " << token.end_pos << "; ";
  return out;
}
