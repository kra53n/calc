#include "Lexer.hpp"

#define is_digit(ch) ('0' - 0 <= ch && ch <= '9' - 0)

std::vector<Token> lex(std::string usr_expr) {
  std::vector<Token> tokens;
  int pos = 0;
  for (auto it = usr_expr.cbegin(); it != usr_expr.cend(); it++) {
    switch (*it) {
    case '+': tokens.push_back(Token { Token::TokenName::Add, "+", pos, pos+1 }); break;
    case '-': tokens.push_back(Token { Token::TokenName::Sub, "-", pos, pos+1 }); break;
    case '*': tokens.push_back(Token { Token::TokenName::Mul, "*", pos, pos+1 }); break;
    case '/': tokens.push_back(Token { Token::TokenName::Mul, "/", pos, pos+1 }); break;
    default:
      if (is_digit(*it)) {
        std::string text;
    	int start_pos = pos;
    	while (is_digit(*it)){
          text = text + *it;
          pos++;
          it++;
    	} 
        tokens.push_back(Token { Token::TokenName::Num, text, start_pos, pos });
      }
      break;
    }
    pos++;
  }
  return tokens;
}
