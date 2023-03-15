#include "interp.hpp"

#include <iostream>

Calculatable* get_type(Token& token) {
  switch (token.name) {
  case Token::TokenName::Num: return new Num(token.text);
  }
}

Calculatable* interp(std::queue<Token>* tokens) {
  std::stack<Calculatable*> st;
  while (tokens->size()) {
    Token tk = tokens->front();
    tokens->pop();
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
      case Token::TokenName::Add: obj2->add(obj1); break;
      case Token::TokenName::Sub: obj2->sub(obj1); break;
      case Token::TokenName::Mul: obj2->mul(obj1); break;
      case Token::TokenName::Div: obj2->div(obj1); break;
      case Token::TokenName::Rtd: obj2->rtd(obj1); break;
        //case Token::TokenName::Sub: st.push(obj1->sub(obj2)); break;
      }
      delete obj1;
      st.push(obj2);
    } break;
    }
  }
  return st.top();
}
