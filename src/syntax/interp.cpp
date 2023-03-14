#include "interp.hpp"

Calculatable* get_type(Token& token) {
  switch (token.name) {
  case Token::TokenName::Num: return new Num(token.text);
  }
}

Calculatable* interp(std::queue<Token>* tokens) {
  std::stack<Calculatable*> st;
  while (tokens->size()) {
    Token tk = tokens->front();
    switch (tk.name) {
    case Token::TokenName::Mx:
    case Token::TokenName::Cx:
    case Token::TokenName::Num:
    case Token::TokenName::BigInt: {
      st.push(get_type(tk));
    } break;
    case Token::TokenName::Add:
    case Token::TokenName::Sub:
    case Token::TokenName::Mul:
    case Token::TokenName::Div:
    case Token::TokenName::Rtd:
    case Token::TokenName::OBrac:
    case Token::TokenName::CBrac: {
      Calculatable* obj1 = st.top();
      st.pop();
      Calculatable* obj2 = st.top();
      st.pop();
      switch (tk.name) {
      case Token::TokenName::Add: st.push(obj1->add(obj2)); break;
      }
    } break;
	}
	tokens->pop();
  }
  return st.top();
}
