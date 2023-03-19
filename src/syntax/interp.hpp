#pragma once

#include <map>
#include <queue>
#include <stack>
#include <string>

#include "Token.hpp"
#include "../math/Num.hpp"
#include "../math/Fraction.hpp"
#include "../math/Calculatable.hpp"

Calculatable* interp(std::queue<Token>* tokens);
