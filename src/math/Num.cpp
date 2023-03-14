#include "Num.hpp"

Num::Num(std::string& text) {
  token_name = Token::TokenName::Num;
  data = stoi(text);
}

std::string Num::result() const {
  return std::to_string(data);
}

int Num::get_data() const {
  return data;
}

Calculatable* Num::add(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Num) {
	this->data += ((Num*)other)->get_data();
  } else {
	// some error here
  }
  return this;
}
