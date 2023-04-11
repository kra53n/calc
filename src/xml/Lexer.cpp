#include "Lexer.hpp"
#include "../util.hpp"

namespace xml {

Lexer::Lexer(std::string& const _file_path)
  : file_path(_file_path)
{
  this->src = new std::fstrem(this->file_path, std::fstrem::in);
}

bool Lexer::is_empty() {
  return cur >= file_path->length();
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
  if (cur + 1 >= file_path->length()) {
    return tk;
  }
  char ch1 = src[cur];
  char ch2 = src[cur+1];
  switch (ch1) {
  case '<': {
    switch (ch2): {
        case '/': tk = new Token(Token::TokenName::OBracWithSlash, "</", row, col); break;
    }
  } break;
  }
  return tk;
}

Token* Lexer::process_single_lexeme() {
  Token* tk = nullptr;
  char ch = src[cur];
  switch (ch) {
  case '<': tk = new Token(Token::TokenName::OBrac, ch, row, bol); break;
  case '>': tk = new Token(Token::TokenName::CBrac, ch, row, bol); break;
  }
  return tk;
}

Token* Lexer::next_token() {
  trim_left();
  while (not is_empty()) {
    Token* tk = nullptr;

    if ((tk = process_double_lexeme())) {
      return tk;
    }

    if ((tk = process_single_lexeme())) {
      return tk;
    }
  }
}

std::vector<Token*>* Lexer::lex() {
  Token* tk;
  while ((tk = next_token())) {
    tokens->push_back(tk);
  }
  return tokens;
}

} // xml
