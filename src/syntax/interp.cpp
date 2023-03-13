#include "interp.hpp"

Base* get_type(Token& token) {
  switch (token.name) {
  case Token::TokenName::Num: return new Num(token.text);
  }
}

Base* interp(std::queue<Token>* tokens) {
  std::stack<Base*> st;
  while (tokens->size()) {
	Token tk = tokens->front();
	switch (tk.name) {
	case Token::TokenName::Mx:
	case Token::TokenName::Cx:
	case Token::TokenName::Num:
	case Token::TokenName::BigInt: {
	  st.push(get_type(tk));
	} break;
	}
  }
  return st.top();
}
