#pragma once

#include <string>
#include <iostream>

struct Token {
  enum class TokenName {
    Add, // +
    Sub, // -
    Mul, // *
    Div, // /
	Rtd, // ** - Raise to degree
    Num,
	OBrac, // (
	CBrac, // )
  };

  TokenName name;
  std::string text;
  int start_pos;
  int end_pos;

  int priority(Token tk) {
	return 1;
  }

  #ifdef TEST
  friend std::ostream& operator<<(std::ostream& out, const Token& token) {
    out << "Text: " << token.text << "; ";
    out << "Start pos: " << token.start_pos << "; ";
    out << "End pos: " << token.end_pos << "; ";
    return out;
  }
  #endif
};
