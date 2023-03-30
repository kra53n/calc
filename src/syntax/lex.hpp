#pragma once

#include <list>
#include <stack>
#include <queue>
#include <vector>
#include <string>
#include <cctype>

#include "Token.hpp"

struct LexChar {
  int pos;
  char ch;
};

std::string get_chars_between(std::queue<LexChar>& chars, char open, char close);
std::list<Token> lex(std::string& usr_expr);
