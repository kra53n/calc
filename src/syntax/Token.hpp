#pragma once

#include <string>

struct Token {
  enum class TokenName {
    Add, // +
    Sub, // -
    Mul, // *
    Div, // /
	Num,
  };

  TokenName name;
  std::string text;
  int start_pos;
}
