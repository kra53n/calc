#pragma once

#include <queue>
#include <stack>

#include "Token.hpp"
#include "../math/Num.hpp"
#include "../math/Base.hpp"

Base* interp(std::queue<Token>* tokens);
