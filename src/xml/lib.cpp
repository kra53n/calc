#include <fstream>

#include "lib.hpp"
#include "Lexer.hpp"

namespace xml {

std::vector<xml::Token*>* _get_tokens(std::string filename) {
  std::fstream file = std::fstream(filename, std::fstream::in);
  std::string string;
  while (file) {
    char ch = (char)file.get();
    string = string + ch;
  }
  return xml::Lexer(string).lex();
}

void _delete_tokens(std::vector<xml::Token*>* tokens) {
  for (xml::Token* it : *tokens) {
    delete it;
  }
  delete tokens;
}

Content get_content(std::string filename) {
  std::vector<Token*>* tokens = _get_tokens(filename);
  Tag* tag = xml::Parser(tokens).parse();
  _delete_tokens(tokens);
  Content res = Interp(tag).interp();
  _delete_tag(tag);
  return res;
}

} // xml