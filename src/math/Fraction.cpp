#include "Num.hpp"
#include "Fraction.hpp"

Fraction::Fraction(std::string& text) {
  std::string integer;
  std::string numerator;
  std::string denominator;
  std::string* curr = &integer;
  for (char ch : text) {
    if (is_skip_char(ch)) {
      continue;
    }
    if (ch == '[') {
      curr = &numerator;
      continue;
    }
    if (ch == '/') {
      curr = &denominator;
      continue;
    }
    *curr = *curr + ch;
  }
  this->token_name = Token::TokenName::Fraction;
  this->data.numerator = std::stoi(numerator);
  this->data.denominator = std::stoi(denominator);
  if (integer != "") {
     this->data.numerator += std::stoi(integer) * this->data.denominator;
  }
  if (this->data.denominator == 0) {
    throw DivisionByZeroError();
  }
}

Fraction::Fraction(Num* num) {
  this->token_name = Token::TokenName::Fraction;
  this->data.numerator = num->get_data();
  this->data.denominator = 1;
}

Fraction::~Fraction() {
}

std::string Fraction::result() const {
  std::string res;
  if (data.numerator / data.denominator) {
    res = std::to_string(data.numerator / data.denominator);
  }
  res = res + "[" + std::to_string(data.numerator % data.denominator) + "/" + std::to_string(data.denominator) + "]";
  return res;
}

Calculable* Fraction::copy() const
{
  std::string res = this->result();
  return new Fraction(res);
}

void Fraction::simplify() {
  int divisor;
  if ((divisor = gcd(data.numerator, data.denominator)) == 1) {
    return;
  }
  data.numerator /= divisor;
  data.denominator /= divisor;
}

Calculable* Fraction::post_treatment() {
  simplify();
  if (data.denominator != 1) {
    return this;
  }
  Num* num = new Num(data.numerator);
  delete this;
  return num;
}

Fraction::_Data Fraction::get_data() const {
  return this->data;
}

Calculable* Fraction::add(Calculable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Fraction: {
    _Data other_data = ((Fraction*)other)->get_data();
    if (this->data.denominator == other_data.denominator) {
      this->data.numerator += other_data.numerator;
      break;
    }
    this->data.numerator = this->data.numerator * other_data.denominator + other_data.numerator * this->data.denominator;
    this->data.denominator *= other_data.denominator;
  } break;
  case Token::TokenName::Num: {
    this->data.numerator += ((Num*)other)->get_data() * this->data.denominator;
  } break;
  default:
    throw IncompatibleTypesError();
    break;
  }
  return post_treatment();
}

Calculable* Fraction::sub(Calculable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Fraction: {
    _Data other_data = ((Fraction*)other)->get_data();
    if (this->data.denominator == other_data.denominator) {
      this->data.numerator -= other_data.numerator;
      return this;
    }
    this->data.numerator = this->data.numerator * other_data.denominator - other_data.numerator * this->data.denominator;
    this->data.denominator *= other_data.denominator;
  } break;
  case Token::TokenName::Num: {
    this->data.numerator -= ((Num*)other)->get_data() * this->data.denominator;
  } break;
  default:
    throw IncompatibleTypesError();
    break;
  }
  return post_treatment();
}

Calculable* Fraction::mul(Calculable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Fraction: {
    _Data other_data = ((Fraction*)other)->get_data();
    this->data.numerator *= other_data.numerator;
    this->data.denominator *= other_data.denominator;
  } break;
  case Token::TokenName::Num: {
    this->data.numerator *= ((Num*)other)->get_data();
  } break;
  default:
    throw IncompatibleTypesError();
    break;
  }
  return post_treatment();
}

Calculable* Fraction::div(Calculable* other) {
  switch (other->get_token_name()) {
  case Token::TokenName::Fraction: {
    _Data other_data = ((Fraction*)other)->get_data();
    this->data.numerator *= other_data.denominator;
    this->data.denominator *= other_data.numerator;
  } break;
  case Token::TokenName::Num: {
    this->data.denominator *= ((Num*)other)->get_data();
  } break;
  default:
    throw IncompatibleTypesError();
    break;
  }
  return post_treatment();
}

Calculable* Fraction::rtd(Calculable* other) {
  if (other->get_token_name() == Token::TokenName::Num) {
    int power = ((Num*)other)->get_data();
    int numerator = this->data.numerator;
    int denominator = this->data.denominator;
    for (int i = 1; i < power; i++) {
      this->data.numerator *= numerator;
      this->data.denominator *= denominator;
    }
    if (power == 0) {
      this->data.numerator = 1;
      this->data.denominator = 1;
    }
  } else {
    throw IncompatibleTypesError();
  }
  return post_treatment();
}
