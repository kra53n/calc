#include "Lexer.hpp"

#define is_digit(ch) ('0' - 0 <= ch && ch <= '9' - 0)

#ifdef TEST
#include <iostream>
#endif
using namespace std;

std::vector<Token> lex(std::string usr_expr) {
  std::vector<Token> tokens;
  int pos = 0;
  for (auto it = usr_expr.cbegin(); it != usr_expr.cend();) {
    switch (*it) {
    case '+': tokens.push_back(Token { Token::TokenName::Add, "+", pos, pos+1 }); break;
    case '-': tokens.push_back(Token { Token::TokenName::Sub, "-", pos, pos+1 }); break;
    case '/': tokens.push_back(Token { Token::TokenName::Mul, "/", pos, pos+1 }); break;
	case '(': tokens.push_back(Token { Token::TokenName::OBrac, "(", pos, pos+1 }); break;
	case ')': tokens.push_back(Token { Token::TokenName::CBrac, ")", pos, pos+1 }); break;
	case '*': {
	  it++;
	  if (*it == '*') {
        tokens.push_back(Token { Token::TokenName::Rtd, "**", pos, pos+2 });
		pos++;
	  } else {
		it--;
        tokens.push_back(Token { Token::TokenName::Mul, "*", pos, pos+1 });
	  }
	} break;
    default: {
	  std::string text;
      int start_pos = pos;

      if (is_digit(*it)) {
        while (is_digit(*it)) {
          text = text + *it;
          pos++;
          it++;
        } 
        tokens.push_back(Token { Token::TokenName::Num, text, start_pos, pos });
		continue;
      }
	} break;
    }
    pos++;
	it++;
  }
  return tokens;
}
