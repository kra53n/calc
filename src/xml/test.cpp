#include <fstream>

#include "Lexer.hpp"
#include "Parser.hpp"

std::vector<xml::Token*>* get_tokens(const char* filename) {
  std::fstream file = std::fstream(filename, std::fstream::in);
  std::string string;
  while (file) {
    char ch = (char)file.get();
    string = string + ch;
  }
  return xml::Lexer(string).lex();
}

int main() {
  //std::string string = "<div     attr1='123123' attr2 attr3>mx((1 0) (0 1))< / div>\n<calc><type>< / type>< / calc>";
  std::vector<xml::Token*>* tokens = get_tokens("test.xml");
  xml::Tag* tag = xml::Parser(tokens).parse();
  delete tokens;
  return 0;
}
