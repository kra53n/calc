#pragma once

#include <string>
#include <unordered_map>

#include "Parser.hpp"

namespace xml {

class Interp {
	Tag* root = nullptr;

	void _process_errors();
public:
	struct Result {
		std::unordered_map<std::string, std::string> vars;
		std::string eval;
	};

	Interp(Tag* root);
	/// return value of `eval` tag from xml, throw errors if file content of xml
	/// not an appropriate structre
	Result interp();
};

} // xml