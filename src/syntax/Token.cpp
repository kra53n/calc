#include "Token.hpp"

int Token::priority(Token& tk) {
  return _token_priority.find(this->name)->second - _token_priority.find(tk.name)->second;
}

bool Token::is_type() {
  switch (name) {
  case TokenName::Num:
  case TokenName::Matrix:
  case TokenName::BigInt:
  case TokenName::Complex:
  case TokenName::Fraction:
    return true;
  }
  return false;
}

std::ostream& operator<<(std::ostream& out, const Token& token) {
  out << "Text: " << token.text << "; ";
  out << "Start pos: " << token.start_pos << "; ";
  out << "End pos: " << token.end_pos << "; ";
  return out;
}

