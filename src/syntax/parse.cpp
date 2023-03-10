#include "parse.hpp"

using namespace std;

// Implementation of Reverse Polish Notation algorithm
queue<Token> parse(vector<Token> tokens) {
  stack<Token> s;
  queue<Token> q;

  for (Token tk : tokens) {
    switch (tk.name) {
    case Token::TokenName::Add:
    case Token::TokenName::Sub:
    case Token::TokenName::Mul:
    case Token::TokenName::Div:
    case Token::TokenName::Rtd:
    case Token::TokenName::OBrac:
    case Token::TokenName::CBrac: {
      if (s.empty() or
          tk.name == Token::TokenName::OBrac or
          tk.priority(s.top()) > 0
      ) {
        s.push(tk);
      } else if (tk.priority(s.top()) <= 0) {
        while (tk.priority(s.top()) > 0 and
               s.top().name != Token::TokenName::OBrac
        ) {
          q.push(s.top());
          s.pop();
        }
        s.push(tk);
      }
    } break;
    case Token::TokenName::Num: {
      q.push(tk);
    } break;
    default: {
      if (tk.name == Token::TokenName::OBrac) {
        s.push(tk);
      } else if (tk.name == Token::TokenName::CBrac) {
        while (s.top().name != Token::TokenName::OBrac) {
          q.push(s.top());
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
    q.push(s.top());
    s.pop();
  }
  
  return q;
}
