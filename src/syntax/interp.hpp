#pragma once

#include <map>
#include <queue>
#include <stack>
#include <string>

#include "Token.hpp"
#include "../math/Num.hpp"
#include "../math/BigInt.hpp"
#include "../math/Matrix.hpp"
#include "../math/Complex.hpp"
#include "../math/Fraction.hpp"
#include "../math/Calculable.hpp"

Calculable* get_type_by_token(Token& token);
Calculable* get_type_by_name_and_val(std::string name, std::string val);

Calculable* interp(
	std::unordered_map<std::string, Calculable*>& vars,
	std::queue<Token>* tokens
);
