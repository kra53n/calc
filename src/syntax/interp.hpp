#pragma once

#include <queue>
#include <stack>

#include "Token.hpp"
#include "../math/Num.hpp"
#include "../math/Fraction.hpp"
#include "../math/Calculatable.hpp"

Calculatable* interp(std::queue<Token>* tokens);
