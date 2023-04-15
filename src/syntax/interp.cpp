#include "interp.hpp"

Calculable* get_type_by_token(Token& token) {
  switch (token.name) {
  case Token::TokenName::Num: return new Num(token.text);
  case Token::TokenName::BigInt: return new BigInt(token.text);
  case Token::TokenName::Matrix: return new Matrix(token.text);
  case Token::TokenName::Complex: return new Complex(token.text);
  case Token::TokenName::Fraction: return new Fraction(token.text);
  }
  return nullptr;
}

Calculable* get_type_by_name_and_val(std::string name, std::string val) {
  if (name == "Num") return new Num(val);
  else if (name == "BigInt") return new BigInt(val);
  else if (name == "Matrix") return new Matrix(val);
  else if (name == "Complex") return new Complex(val);
  else if (name == "Fraction") return new Fraction(val);
  return nullptr;
}

Calculable* interp(
  std::unordered_map<std::string, Calculable*>& vars,
  std::queue<Token>* tokens
) {
  std::stack<Calculable*> st;
  while (tokens->size()) {
    Token tk = tokens->front();
    tokens->pop();
    switch (tk.name) {
    case Token::TokenName::AssignVar: {
      if (vars.count(tk.text)) {
        delete vars[tk.text];
      }
      vars[tk.text] = st.top()->copy();
      vars[tk.text]->is_var = true;
      st.pop();
      return nullptr;
    } break;
    case Token::TokenName::Var:
    case Token::TokenName::Num:
    case Token::TokenName::BigInt:
    case Token::TokenName::Matrix:
    case Token::TokenName::Complex:
    case Token::TokenName::Fraction: {
      if (tk.name == Token::TokenName::Var) {
        st.push(vars[tk.text]);
        continue;
      }
      st.push(get_type_by_token(tk));
    } break;
    case Token::TokenName::Add:
    case Token::TokenName::Sub:
    case Token::TokenName::Mul:
    case Token::TokenName::Div:
    case Token::TokenName::Rtd:
    case Token::TokenName::OBrac:
    case Token::TokenName::CBrac: {
      Calculable* obj1 = st.top()->copy();
      st.pop();
      Calculable* obj2 = st.top()->copy();
      st.pop();
      switch (tk.name) {
      case Token::TokenName::Add: obj2 = obj2->add(obj1); break;
      case Token::TokenName::Sub: obj2 = obj2->sub(obj1); break;
      case Token::TokenName::Mul: obj2 = obj2->mul(obj1); break;
      case Token::TokenName::Div: obj2 = obj2->div(obj1); break;
      case Token::TokenName::Rtd: obj2 = obj2->rtd(obj1); break;
      }
      if (not obj1->is_var) {
        delete obj1;
      }
      st.push(obj2);
    } break;
    }
  }
  return st.size() ? st.top() : nullptr;
}
