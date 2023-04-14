#include "Lexer.hpp"
#include "../util.hpp"

namespace xml {

Lexer::Lexer(std::string& const src)
  : src(src)
  , cur(0)
  , bol(0)
  , row(0)
{
  tokens = new std::vector<Token*>;
}

bool Lexer::_is_empty() {
  return cur >= src.length();
}

void Lexer::_chop_char() {
  if (_is_empty()) {
    return;
  }
  cur++;
  if (src[cur-1] == '\n') {
    row++;
    bol = cur;
  }
}

void Lexer::_trim_left() {
  while (not _is_empty() and is_skip_char(src[cur])) {
    _chop_char();
  }
}

Token* Lexer::_process_double_lexeme() {
  Token* tk = nullptr;
  if (cur + 1 >= src.length()) {
    return tk;
  }
  char ch1 = src[cur];
  char ch2 = src[cur+1];
  switch (ch1) {
  case '<': {
    switch (ch2) {
    case '/': tk = new Token(Token::TokenName::OBracWithSlash, "</", row, cur-bol); break;
    }
  } break;
  }
  if (tk) {
    _chop_char();
  }
  return tk;
}

Token* Lexer::_process_single_lexeme() {
  Token* tk = nullptr;
  char ch = src[cur];
  switch (ch) {
  case '<': tk = new Token(Token::TokenName::OBrac, "<", row, cur-bol); break;
  case '>': tk = new Token(Token::TokenName::CBrac, ">", row, cur-bol); break;
  }
  if (tk) {
    _chop_char();
  }
  return tk;
}

bool Lexer::_is_part_of_plural_lexeme() {
  return (
    not _is_empty() and
    not (src[cur] == '<' ^ src[cur] == '>') and
    (
      not is_skip_char(src[cur]) or
      (
        tokens->size() and
        (*tokens)[tokens->size()-1]->name == Token::TokenName::CBrac
      )
    )
  );
}

Token* Lexer::_process_plural_lexeme() {
  Token* tk = nullptr;
  std::string lexeme;
  int start_col = cur - bol;

  while (_is_part_of_plural_lexeme()) {
    lexeme = lexeme + src[cur];
    _chop_char();
  }

  if (lexeme != "") {
    Token::TokenName tk_name = (*tokens)[tokens->size()-1]->name;
    if (
      tk_name == Token::TokenName::OBrac or
      tk_name == Token::TokenName::OBracWithSlash
    ) {
      tk = new Token(Token::TokenName::TagName, lexeme, row, start_col);
    }
    else if (tk_name == Token::TokenName::CBrac) {
      tk = new Token(Token::TokenName::Val, lexeme, row, start_col);
    }
    else if (
      tk_name == Token::TokenName::TagName or
      tk_name == Token::TokenName::Attr
    ) {
      tk = new Token(Token::TokenName::Attr, lexeme, row, start_col);
    }
  }

  return tk;
}

Token* Lexer::next_token() {
  while (not _is_empty()) {
    _trim_left();
    Token* tk = nullptr;
    if (
      (tk = _process_double_lexeme()) or
      (tk = _process_single_lexeme()) or
      (
        (isalnum(src[cur]) or src[cur] == '(') and
        (tk = _process_plural_lexeme())
      )
    ) {
      return tk;
    }
    else {
      _chop_char();
    }
  }
  return nullptr;
}

std::vector<Token*>* Lexer::lex() {
  Token* tk;
  while ((tk = next_token())) {
    tokens->push_back(tk);
  }
  return tokens;
}

} // xml
