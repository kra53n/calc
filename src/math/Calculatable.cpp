#include "Calculatable.hpp"

std::ostream& operator<<(std::ostream& out, const Calculatable& calculatable) {
  out << calculatable.result();
  return out;
}

Token::TokenName Calculatable::get_token_name() {
  return token_name;
}
