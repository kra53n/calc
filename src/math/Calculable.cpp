#include "Calculable.hpp"

std::ostream& operator<<(std::ostream& out, const Calculable& Calculable) {
  out << Calculable.result();
  return out;
}

Token::TokenName Calculable::get_token_name() {
  return token_name;
}
