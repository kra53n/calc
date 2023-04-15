#pragma once

#include <queue>
#include <vector>
#include <iostream>

#include "errors.hpp"
#include "syntax/lex.hpp"
#include "syntax/parse.hpp"
#include "syntax/interp.hpp"

#include "xml/xml_lib.hpp"
#include "xml/xml_error.hpp"

void repl();
void process_xml(std::string filename);