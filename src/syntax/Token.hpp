#pragma once

#include <iostream>
#include <unordered_map>

struct Token {
  enum class TokenName {
    Add, // +
    Sub, // -
    Mul, // *
    Div, // /
    Rtd, // ** - Raise to degree
    UnaryMinus,
    OBrac, // (
    CBrac, // )
    Num,
    BigInt,
    Fraction,
    Var, // Variable
    AssignVar,
    Matrix,
    Complex,
  };

  TokenName name;
  std::string text;
  int start_pos;
  int end_pos;

  int priority(Token& tk);
  bool is_type();
  friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

const std::unordered_map<Token::TokenName, int> _token_priority = {
  { Token::TokenName::AssignVar, 0 },
  { Token::TokenName::Add, 1 },
  { Token::TokenName::Sub, 1 },
  { Token::TokenName::Mul, 2 },
  { Token::TokenName::Div, 2 },
  { Token::TokenName::Rtd, 3 },
  { Token::TokenName::OBrac, 4 },
  { Token::TokenName::CBrac, 4 },
  { Token::TokenName::UnaryMinus, 5 },
};

