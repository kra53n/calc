#include "lex.hpp"

// Get args from function
// E.g.:
//   Input: substr -> matrix((1 2) (2 1))
//   Input: keyword -> matrix
//   Output: text -> (1 2) (2 1)
//   Output: start_pos -> 7
//   Output: end_pos -> 19
bool get_sub_expr_args(
  std::string substr,
  std::string keyword,
  std::string& text,
  int& start_pos,
  int& end_pos
) {
  int pos = substr.find(keyword);
  if (pos == std::string::npos or pos != 0) {
    return false;
  }
  std::stack<char> st;
  pos = substr.find("(");
  // TODO: here must be thrown an error
  if (pos == std::string::npos) {
    return false;
  }
  st.push('(');
  pos++;
  start_pos = pos;
  while (st.size() and pos < substr.length()) {
    switch (substr[pos]) {
    case '(': st.push('('); break;
    case ')': st.pop(); break;
    }
    pos++;
  }
  end_pos = pos;
  text = substr.substr(start_pos, end_pos-start_pos-1);
  return true;
}

std::vector<Token> lex(std::string usr_expr) {
  std::vector<Token> tokens;
  for (int pos = 0; pos < usr_expr.length(); pos++) {
    switch (usr_expr[pos]) {
    case '\n':
    case '\t':
    case ' ':
      continue;
    case '+': tokens.push_back(Token { Token::TokenName::Add, "+", pos, pos+1 }); break;
    case '-': tokens.push_back(Token { Token::TokenName::Sub, "-", pos, pos+1 }); break;
    case '/': tokens.push_back(Token { Token::TokenName::Mul, "/", pos, pos+1 }); break;
    case '(': tokens.push_back(Token { Token::TokenName::OBrac, "(", pos, pos+1 }); break;
    case ')': tokens.push_back(Token { Token::TokenName::CBrac, ")", pos, pos+1 }); break;
    case '*': {
      pos++;
      if (usr_expr[pos] == '*') {
        tokens.push_back(Token { Token::TokenName::Rtd, "**", pos-1, pos+1 });
      } else {
        pos--;
        tokens.push_back(Token { Token::TokenName::Mul, "*", pos, pos+1 });
      }
    } break;
    default: {
      std::string text;
      int start_pos = pos;

      if (isdigit(usr_expr[pos])) {
        while (isdigit(usr_expr[pos])) {
          text = text + usr_expr[pos];
          pos++;
        } 
        tokens.push_back(Token { Token::TokenName::Num, text, start_pos, pos });
        continue;
      }

      std::string substr = usr_expr.substr(pos, usr_expr.length()-pos);
      int end_pos;
      for (std::string keyword : { "complex", "cx", "matrix", "mx" }) {
        if (get_sub_expr_args(substr, keyword, text, start_pos, end_pos)) {
          tokens.push_back(Token { Token::TokenName::Cx, text, pos, end_pos+1 });
          pos += end_pos;
          break;
        };
      }
    }
    }
  }
  return tokens;
}
