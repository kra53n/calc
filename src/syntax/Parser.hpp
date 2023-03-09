#pragma once

#include <stack>
#include <vector>
#include "Token.hpp"

std::stack<Token> parse(std::vector<Token> tokens);
