#include "Fraction.hpp"

Fraction::Fraction(std::string& text) {
  std::string numerator;
  std::string denominator;
  std::string* curr = &numerator;
  for (char ch : text) {
    switch (ch) {
    case ' ':
    case '\t':
    case '\n':
      continue;
    case '/':
      curr = &denominator;
      continue;
    }
    *curr = *curr + ch;
  }
  this->token_name = Token::TokenName::Fraction;
  this->data.numerator = std::stoi(numerator);
  this->data.denominator = std::stoi(denominator);
}

std::string Fraction::result() const {
  std::string res = "[" + std::to_string(this->data.numerator) + "/" + std::to_string(this->data.denominator) + "]";
  return res;
}

Fraction::_Data Fraction::get_data() const {
  return this->data;
}

Calculatable* Fraction::add(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Fraction) {
    _Data other_data = ((Fraction*)other)->get_data();
    if (this->data.denominator == other_data.denominator) {
      this->data.numerator += other_data.numerator;
      return this;
    }
    this->data.numerator = this->data.numerator * other_data.denominator + other_data.numerator * this->data.denominator;
    this->data.denominator *= other_data.denominator;
  } else {
    // error
  }
  return this;
}

Calculatable* Fraction::sub(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Fraction) {
    _Data other_data = ((Fraction*)other)->get_data();
    if (this->data.denominator == other_data.denominator) {
      this->data.numerator -= other_data.numerator;
      return this;
    }
    this->data.numerator = this->data.numerator * other_data.denominator - other_data.numerator * this->data.denominator;
    this->data.denominator *= other_data.denominator;
  } else {
    // error
  }
  return this;
}

Calculatable* Fraction::mul(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Fraction) {
    _Data other_data = ((Fraction*)other)->get_data();
    this->data.numerator *= other_data.numerator;
    this->data.denominator *= other_data.denominator;
  } else {
    // error
  }
  return this;
}

Calculatable* Fraction::div(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Fraction) {
    _Data other_data = ((Fraction*)other)->get_data();
    this->data.numerator *= other_data.denominator;
    this->data.denominator *= other_data.numerator;
  } else {
    // error
  }
  return this;
}

Calculatable* Fraction::rtd(Calculatable* other) {
  if (other->get_token_name() == Token::TokenName::Num) {
    int power = ((Num*)other)->get_data();
    int numerator = this->data.numerator;
    int denominator = this->data.denominator;
    for (int i = 1; i < power; i++) {
      this->data.numerator *= numerator;
      this->data.denominator *= denominator;
    }
  } else {
    // error
  }
  return this;
}