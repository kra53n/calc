#include "Parser.hpp"

using namespace std;

stack<Token> parse(vector<Token> tokens) {
  // stack<Token> s;
  // queue<Token> q;
  // Token operation;
  // bool is_operation_loaded = false;

  // for (Token tk : tokens) {
  // 	switch (tk.name) {
  // 	case Token::TokenName::Add:
  // 	case Token::TokenName::Sub:
  // 	case Token::TokenName::Mul:
  // 	case Token::TokenName::Div:
  // 	  operation = tk;
  // 	  is_operation_loaded = true;
  // 	  break;
  // 	default:
  // 	  st.push(tk);
  // 	  if (is_operation_loaded) {
  // 		st.push(operation);
  // 		is_operation_loaded = false;
  // 	  }
  // 	  break;
  // 	}
  // }

// stack<Token> parse(vector<Token> tokens) {
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
		while () {
		}
	  }
	} break;
	case Token::TokenName::Num: {
	  q.push(tk);
	} break;
	}
  }
  
  return s;
}
