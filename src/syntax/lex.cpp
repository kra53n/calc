#include "lex.hpp"


std::string get_expr_between(std::string expr, char open, char close) {
  int pos = 0;
  std::stack<char> st;
  st.push(expr[pos++]);
  while (st.size() and pos < expr.length()) {
    if (expr[pos] == open) {
      st.push(open);
    } else if (expr[pos] == close) {
      st.pop();
    }
    pos++;
  }
  return expr.substr(1, pos-2);
}

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
  int& end_pos,
  char open = '(',
  char close = ')'
) {
  int pos = substr.find(keyword);
  if (pos == std::string::npos or pos != 0) {
    return false;
  }
  pos = substr.find(open);
  // TODO: here must be thrown an error
  if (pos == std::string::npos) {
    return false;
  }
  text = get_expr_between(substr.substr(pos), open, close);
  start_pos = pos + 1;
  end_pos = pos + text.length();
  return true;
}

std::vector<Token> lex(std::string usr_expr) {
  std::cout << get_expr_between("(12 12 12)", '(', ')') << std::endl;
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
    case '[': {
      std::string text = get_expr_between(usr_expr.substr(pos), '[', ']');
      tokens.push_back(Token { Token::TokenName::Fraction, text, pos+1, pos+text.length()+1 });
      pos += text.length();
    } break;
    default: {
      std::string text;
      int start_pos = pos;

      if (isdigit(usr_expr[pos])) {
        if (pos > 0 and usr_expr[pos-1] == '-') {
          text = text + '-';
        }
        while (isdigit(usr_expr[pos])) {
          text = text + usr_expr[pos];
          pos++;
        } 
        tokens.push_back(Token {
          text.compare("2147483647") <= 0 ?
            Token::TokenName::Num :
             Token::TokenName::BigInt,
          text,
          start_pos,
          pos
        });
        continue;
      }

      bool to_continue = false;
      std::string substr = usr_expr.substr(pos, usr_expr.length()-pos);
      int end_pos;
      for (std::string keyword : { "complex", "cx", "matrix", "mx" }) {
        if (get_sub_expr_args(substr, keyword, text, start_pos, end_pos)) {
          start_pos += pos;
          end_pos += pos;
          tokens.push_back(Token { Token::TokenName::Cx, text, start_pos, end_pos+1 });
          to_continue = true;
          pos = end_pos;
          break;
        };
      }
      if (to_continue) {
        continue;
      }
  }
  return tokens;
}
