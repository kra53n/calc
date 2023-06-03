#include <malloc.h>

#include "xml_Error.hpp"
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

void Parser::_handle_attr_health(Tag::Attr& attr) {
  std::vector<std::string> ok_names = {
    "type",
    "vars",
    "name",
  };
  if (std::find(ok_names.begin(), ok_names.end(), attr.name) == ok_names.end()) {
    std::string message = "not possible to use `" + attr.name + "` attribute name";
    throw Error(message);
  }
  if (attr.name == "type") {
    std::vector<std::string> ok_val_names = {
      "Num",
      "Fraction",
      "Matrix",
      "Complex",
      "Cx",
    };
		if (std::find(ok_val_names.begin(), ok_val_names.end(), attr.val) == ok_val_names.end()) {
			std::string message = "not possible to use `" + attr.val + "` attribute value";
			throw Error(message);
		}
  }
}

void Parser::_handle_tag_health(Tag* tag) {
  std::vector<std::string> ok_names = {
    "calc",
    "vars",
    "type",
    "var",
    "eval"
  };
  if (std::find(ok_names.begin(), ok_names.end(), tag->name) == ok_names.end()) {
    std::string message = "not possible to use `" + tag->name + "` tag name";
    throw Error(message);
  }
	for (auto attr : tag->attrs) {
		_handle_attr_health(attr);
	}
}

Tag* Parser::parse() {
  std::stack<Tag*> st;
  while (not _empty()) {
    bool closing;
    Tag* tag = _collect_tag(closing);
    _handle_tag_health(tag);

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