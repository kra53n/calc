#pragma once

#include <string>

#include "Parser.hpp"

namespace xml {

/// return value of `eval` tag from xml, throw errors if file content of xml
/// not an appropriate structre
std::string interp(Tag* root);

} // xml