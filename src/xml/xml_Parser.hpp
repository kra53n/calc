#pragma once

#include <stack> 
#include <vector>

#include "xml_Token.hpp"

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

void _delete_tag_recursively(Tag* tag);
void _delete_tag(Tag* tag);

class Parser {
  int pos;
  std::vector<Token*>* tokens = nullptr;

  bool _empty();

  void _handle_attr_health(Tag::Attr& attr);
  void _handle_tag_health(Tag* tag);

  Tag::Attr _parse_attr(Token* token);
  Tag* _collect_tag(bool& closing);
public:
  Parser(std::vector<Token*>* tokens);
  Tag* parse();
};

} // xml