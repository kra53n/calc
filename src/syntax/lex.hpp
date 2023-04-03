#pragma once

#include <list>
#include <queue>
#include <string>

#include "Token.hpp"
#include "../util.hpp"

struct LexChar {
  int pos;
  char ch;
};

std::string get_chars_between(std::queue<LexChar>& chars, char open, char close);
std::list<Token> lex(std::string& usr_expr);
