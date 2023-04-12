#pragma once

#include <stack> 
#include <vector>

#include "Token.hpp"

namespace xml {

struct Tag {
  struct Attr {
    std::string name;
    std::string val;
  };

  std::string name;
  std::vector<Attr> attrs;
  std::string* val = nullptr;
  std::vector<Tag*> tags;
};

class Parser {
  int pos;
  std::vector<Token*>* tokens = nullptr;

  bool _empty();

  Tag::Attr _parse_attr(Token* token);
  Tag* _collect_tag(bool& closing);
public:
  Parser(std::vector<Token*>* tokens);
  Tag* parse();
};

} // xml