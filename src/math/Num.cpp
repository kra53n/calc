#include "Num.hpp"

Num::Num(std::string& text) {
  token_name = Token::TokenName::Num;
  data = stoi(text);
}

Num::Num(int num) {
  token_name = Token::TokenName::Num;
  data = num;
}

Num::~Num() {
}

std::string Num::result() const {
  return std::to_string(data);
}

int Num::get_data() const {
  return data;
}

Calculatable* Num::add(Calculatable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Num: {
    this->data += ((Num*)other)->get_data();
  } break;
  case Token::TokenName::Fraction: {
    Fraction* fraction = new Fraction(this);
    fraction->add(other);
    delete this;
    return fraction;
  } break;
  default:
    // error
    break;
  }
  return this;
}

Calculatable* Num::sub(Calculatable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Num: {
    this->data -= ((Num*)other)->get_data();
  } break;
  case Token::TokenName::Fraction: {
    Fraction* fraction = new Fraction(this);
    fraction->sub(other);
    delete this;
    return fraction;
  } break;
  default:
    // error
    break;
  }
  return this;
}

Calculatable* Num::mul(Calculatable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Num: {
    this->data *= ((Num*)other)->get_data();
  } break;
  case Token::TokenName::Fraction: {
    Fraction* fraction = new Fraction(this);
    fraction->mul(other);
    delete this;
    return fraction;
  } break;
  default:
    // error
    break;
  }
  return this;
}

Calculatable* Num::div(Calculatable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Num: {
    this->data /= ((Num*)other)->get_data();
  } break;
  case Token::TokenName::Fraction: {
    Fraction* fraction = new Fraction(this);
    fraction->div(other);
    delete this;
    return fraction;
  } break;
  default:
    // error
    break;
  }
  return this;
}

Calculatable* Num::rtd(Calculatable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Num: {
    int power = ((Num*)other)->get_data();
    int tmp = this->data;
    for (int i = 0; i < power-1; i++) {
      this->data *= tmp;
    }
    if (power == 0) {
      this->data = 1;
    }
  } break;
  case Token::TokenName::Fraction: {
    Fraction* fraction = new Fraction(this);
    fraction->rtd(other);
    delete this;
    return fraction;
  } break;
  default:
    // error
    break;
  }
  return this;
}
