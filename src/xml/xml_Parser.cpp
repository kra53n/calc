#include <malloc.h>

#include "xml_Parser.hpp"

namespace xml {

void _delete_tag_recursively(Tag* tag) {
  if (tag->tags.size()) {
    for (Tag* it : tag->tags) {
      _delete_tag_recursively(it);
      delete it;
    }
  }
  if (tag->val) {
    delete tag->val;
  }
}

void _delete_tag(Tag* tag) {
  _delete_tag_recursively(tag);
  delete tag;
}

Parser::Parser(std::vector<Token*>* tokens)
  : tokens(tokens)
  , pos(0)
{
}

bool Parser::_empty() {
  return pos >= tokens->size();
}

Tag::Attr Parser::_parse_attr(Token* token) {
  Tag::Attr attr;
  std::string* buf = &attr.name;
  for (char ch : token->lexeme) {
    switch (ch) {
    case '=':
    case '"':
    case '\'':
      if (ch == '=') {
        buf = &attr.val;
      }
      continue;
    }
    *buf = *buf + ch;
  }
  return attr;
}

Tag* Parser::_collect_tag(bool& closing) {
  if (_empty()) {
    return nullptr;
  }
  Tag* tag = new Tag;
  Token* token;
  do {
    token = (*tokens)[pos++];

    switch (token->name) {
    case Token::TokenName::OBrac:
    case Token::TokenName::OBracWithSlash: {
      closing = token->name == Token::TokenName::OBracWithSlash;
    } continue;
    case Token::TokenName::TagName: {
      tag->name = token->lexeme;
    } break;
    case Token::TokenName::Attr: {
      tag->attrs.push_back(_parse_attr(token));
    } break;
    }
  } while (not _empty() and token->name != Token::TokenName::CBrac);

  if (not _empty()) {
    token = (*tokens)[pos];
    switch (token->name) {
    case Token::TokenName::Val: {
      tag->val = new std::string(token->lexeme);
    } break;
    }
  }

  return tag;
}

Tag* Parser::parse() {
  std::stack<Tag*> st;
  while (not _empty()) {
    bool closing;
    Tag* tag = _collect_tag(closing);

    if (not closing) {
      st.push(tag);
    }

    if (st.size() == 1) {
      continue;
    }

    if (closing) {
      Tag* tmp = st.top();
      st.pop();
      st.top()->tags.push_back(tmp);
    }
  }
  return st.size() ? st.top() : nullptr;
}

} // xml