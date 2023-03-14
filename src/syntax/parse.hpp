#pragma once

#include <stack>
#include <queue>
#include <vector>

#include "Token.hpp"

std::queue<Token>* parse(std::vector<Token> tokens);
