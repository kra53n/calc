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

bool Lexer::is_empty() {
  return cur >= src.length();
}

void Lexer::chop_char() {
  if (is_empty()) {
    return;
  }
  cur++;
  if (src[cur-1] == '\n') {
    row++;
    bol = cur;
  }
}

void Lexer::trim_left() {
  while (not is_empty() and is_skip_char(src[cur])) {
    chop_char();
  }
}

Token* Lexer::process_double_lexeme() {
  Token* tk = nullptr;
  if (cur + 1 >= src.length()) {
    return tk;
  }
  char ch1 = src[cur];
  char ch2 = src[cur+1];
  switch (ch1) {
  case '<': {
    switch (ch2) {
    case '/': tk = new Token(Token::TokenName::OBracWithSlash, "</", row, bol); break;
    }
  } break;
  }
  if (tk) {
    chop_char();
  }
  return tk;
}

Token* Lexer::process_single_lexeme() {
  Token* tk = nullptr;
  char ch = src[cur];
  switch (ch) {
  case '<': tk = new Token(Token::TokenName::OBrac, "<", row, bol); break;
  case '>': tk = new Token(Token::TokenName::CBrac, ">", row, bol); break;
  }
  if (tk) {
    chop_char();
  }
  return tk;
}

Token* Lexer::process_alpha_lexeme() {
  Token* tk = nullptr;
  std::string lexeme;
  int start_col = bol;

  while (not is_empty() && (isalpha(src[cur]) || isdigit(src[cur]))) {
    lexeme = lexeme + src[cur];
    chop_char();
  }

  if (tokens->empty()) {
    return tk;
  }

  if (lexeme != "") {
    Token::TokenName tk_name = (*tokens)[tokens->size()-1]->name;
    if (
      tk_name == Token::TokenName::OBrac or
      tk_name == Token::TokenName::OBracWithSlash
    ) {
      tk = new Token(Token::TokenName::TagName, lexeme.c_str(), row, start_col);
    }
    else if (tk_name == Token::TokenName::CBrac) {
      tk = new Token(Token::TokenName::Elem, lexeme.c_str(), row, start_col);
    }
  }

  return tk;
}

Token* Lexer::next_token() {
  while (not is_empty()) {
    trim_left();

    Token* tk = nullptr;

    if ((tk = process_double_lexeme())) {
      return tk;
    }

    if ((tk = process_single_lexeme())) {
      return tk;
    }

    if (isalpha(src[cur]) || isdigit(src[cur])) {
      if ((tk = process_alpha_lexeme())) {
        return tk;
      }
    }

    // TODO: delete condition below
    if (not tk) {
      chop_char();
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
