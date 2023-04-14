#include <fstream>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Interp.hpp"

std::vector<xml::Token*>* get_tokens(const char* filename) {
  std::fstream file = std::fstream(filename, std::fstream::in);
  std::string string;
  while (file) {
    char ch = (char)file.get();
    string = string + ch;
  }
  return xml::Lexer(string).lex();
}

void delete_tokens(std::vector<xml::Token*>* tokens) {
  for (xml::Token* it : *tokens) {
    delete it;
  }
  delete tokens;
}

int main() {
  std::vector<xml::Token*>* tokens = get_tokens("test.xml");
  xml::Token* tmp = (*tokens)[0];
  xml::Tag* tag = xml::Parser(tokens).parse();
  xml::Interp interp(tag);
  xml::Result res = interp.interp();
  delete_tokens(tokens);
  return 0;
}
