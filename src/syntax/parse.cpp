#include "parse.hpp"

// TODO: find problem of rpn implementation

// Implementation of Reverse Polish Notation algorithm
std::queue<Token>* parse(std::list<Token> tokens) {
  std::stack<Token> s;
  std::queue<Token>* q = new std::queue<Token>;

  for (Token tk : tokens) {
    switch (tk.name) {
    case Token::TokenName::Add:
    case Token::TokenName::Sub:
    case Token::TokenName::Mul:
    case Token::TokenName::Div:
    case Token::TokenName::Rtd:
    case Token::TokenName::AssignVar: {
      if (s.empty() or
          s.top().name == Token::TokenName::OBrac or
          tk.priority(s.top()) > 0
      ) {
        s.push(tk);
      } else if (tk.priority(s.top()) <= 0) {
        while (s.size() and
               tk.priority(s.top()) <= 0 and
               s.top().name != Token::TokenName::OBrac
        ) {
          q->push(s.top());
          s.pop();
        }
        s.push(tk);
      }
    } break;
    case Token::TokenName::Num:
    case Token::TokenName::Var:
    case Token::TokenName::BigInt:
    case Token::TokenName::Matrix:
    case Token::TokenName::Complex:
    case Token::TokenName::Fraction: {
      q->push(tk);
    } break;
    default: {
      if (tk.name == Token::TokenName::OBrac) {
        s.push(tk);
      } else if (tk.name == Token::TokenName::CBrac) {
        while (s.top().name != Token::TokenName::OBrac) {
          q->push(s.top());
          s.pop();
        }
        s.pop();
      }
    } break;
    }
  }

  while (s.size()) {
    switch (s.top().name) {
    case Token::TokenName::OBrac:
    case Token::TokenName::CBrac:
      s.pop();
      continue;
    }
    q->push(s.top());
    s.pop();
  }

  return q;
}
