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
    OBrac, // (
    CBrac, // )
    Num,
    BigInt,
	Fraction,
    Var, // Variable
    Mx, // Matrix
    Cx, // Complex
  };

  TokenName name;
  std::string text;
  int start_pos;
  int end_pos;

  int priority(Token& tk);
  friend std::ostream& operator<<(std::ostream& out, const Token& token);
};

const std::unordered_map<Token::TokenName, int> _token_priority = {
  { Token::TokenName::Add, 0 },
  { Token::TokenName::Sub, 0 },
  { Token::TokenName::Mul, 1 },
  { Token::TokenName::Div, 1 },
  { Token::TokenName::Rtd, 2 },
  { Token::TokenName::OBrac, 3 },
  { Token::TokenName::CBrac, 3 },
};
