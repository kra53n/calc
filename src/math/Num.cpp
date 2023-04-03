#include "Num.hpp"
#include "BigInt.hpp"
#include "Complex.hpp"

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

Calculable* Num::copy() const {
  return new Num(this->get_data());
}

int Num::get_data() const {
  return data;
}

Calculable* Num::add(Calculable* other) {
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
  case Token::TokenName::Complex: {
    Complex* complex = new Complex(this->data);
    complex->add(other);
    delete this;
    return complex;
  } break;
  case Token::TokenName::BigInt: {
    BigInt* bigint = new BigInt(std::to_string(this->data));
    bigint->add(other);
    delete this;
    return bigint;
  } break;
  default:
    throw IncompatibleTypesError();
    break;
  }
  return this;
}

Calculable* Num::sub(Calculable* other) {
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
  case Token::TokenName::Complex: {
    Complex* complex = new Complex(this->data);
    complex->sub(other);
    delete this;
    return complex;
  } break;
  case Token::TokenName::BigInt: {
    BigInt* bigint = new BigInt(std::to_string(this->data));
    bigint->sub(other);
    delete this;
    return bigint;
  } break;
  default:
    throw IncompatibleTypesError();
    break;
  }
  return this;
}

Calculable* Num::mul(Calculable* other) {
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
  case Token::TokenName::Complex: {
    Complex* complex = new Complex(this->data);
    complex->mul(other);
    delete this;
    return complex;
  } break;
  case Token::TokenName::BigInt: {
    BigInt* bigint = new BigInt(std::to_string(this->data));
    bigint->mul(other);
    delete this;
    return bigint;
  } break;
  default:
    throw IncompatibleTypesError();
    break;
  }
  return this;
}

Calculable* Num::div(Calculable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Num: {
    int data = ((Num*)other)->get_data();
    if (data == 0) {
      throw DivisionByZeroError();
    }
    this->data /= data;
  } break;
  case Token::TokenName::Fraction: {
    Fraction* fraction = new Fraction(this);
    fraction->div(other);
    delete this;
    return fraction;
  } break;
  case Token::TokenName::Complex: {
    Complex* complex = new Complex(this->data);
    complex->div(other);
    delete this;
    return complex;
  } break;
  case Token::TokenName::BigInt: {
    BigInt* bigint = new BigInt(std::to_string(this->data));
    bigint->div(other);
    delete this;
    return bigint;
  } break;
  default:
    throw IncompatibleTypesError();
    break;
  }
  return this;
}

Calculable* Num::rtd(Calculable* other) {
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
  case Token::TokenName::Complex: {
    Complex* complex = new Complex(this->data);
    complex->rtd(other);
    delete this;
    return complex;
  } break;
  case Token::TokenName::BigInt: {
    BigInt* bigint = new BigInt(std::to_string(this->data));
    bigint->rtd(other);
    delete this;
    return bigint;
  } break;
  default:
    throw IncompatibleTypesError();
    break;
  }
  return this;
}
