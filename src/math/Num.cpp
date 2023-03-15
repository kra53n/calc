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

Calculatable* Num::sub(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Num) {
    this->data -= ((Num*)other)->get_data();
  } else {
    // some error here
  }
  return this;
}

Calculatable* Num::mul(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Num) {
    this->data *= ((Num*)other)->get_data();
  } else {
    // some error here
  }
  return this;
}

Calculatable* Num::div(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Num) {
    this->data /= ((Num*)other)->get_data();
  } else {
    // some error here
  }
  return this;
}

Calculatable* Num::rtd(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Num) {
    int power = ((Num*)other)->get_data();
    int tmp = this->data;
    for (int i = 0; i < power-1; i++) {
      this->data *= tmp;
    }
    if (power == 0) {
      this->data = 1;
    }
  } else {
    // some error here
  }
  return this;
}
