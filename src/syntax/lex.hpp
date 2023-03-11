#pragma once

#include <stack>
#include <vector>
#include <string>

#include "Token.hpp"

std::vector<Token> lex(std::string usr_expr);
