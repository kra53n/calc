#include "lex.hpp"

std::queue<LexChar> get_chars(std::string& usr_expr) {
  std::queue<LexChar> q;
  for (int i = 0; i < usr_expr.length(); i++) {
    char ch = usr_expr[i];
    q.push(LexChar { i, ch });
  }
  return q;
}

Token process_digit(std::queue<LexChar>& chars, int pos) {
  std::string text;
  int end_pos = pos;
  for (; chars.size() and isdigit(chars.front().ch); chars.pop()) {
    text = text + chars.front().ch;
    end_pos = chars.front().pos;
  }
  return Token { Token::TokenName::Num, text, pos, end_pos+1 };
}

// input: ((1 2) (2 1))...
// output: (1 2) (2 1)
//
// input: (1 2i)...
// output: 1 2i
std::string get_chars_between(std::queue<LexChar>& chars, char open, char close) {
  std::string text;
  std::stack<char> st;
  do {
    if (chars.front().ch == open) {
      st.push(open);
    }
    else if (chars.front().ch == close) {
      st.pop();
    }
    text = text + chars.front().ch;
    chars.pop();
  } while (st.size() and chars.size());
  return text.substr(1, text.length()-2);
}

Token process_symbols(std::queue<LexChar>& chars, int pos) {
  std::string text;
  int end_pos = pos;
  for (; chars.size() and
         (isalpha(chars.front().ch) or
          chars.front().ch == ' ' or
          chars.front().ch == '\t');
      chars.pop()) {
    switch (chars.front().ch) {
    case ' ':
    case '\t':
      continue;
    }
    text = text + chars.front().ch;
    end_pos = chars.front().pos;
    // TODO: add process_matrix function
    // TODO: add process_complex function
    if (not text.compare("matrix") or not text.compare("mx")) {
      chars.pop();
      text = get_chars_between(chars, '(', ')');
      end_pos += text.length();
      return Token { Token::TokenName::Matrix, text, pos, end_pos+3 };
    }
    if (not text.compare("complex") or not text.compare("cx")) {
      chars.pop();
      text = get_chars_between(chars, '(', ')');
      end_pos += text.length();
      return Token{ Token::TokenName::Complex, text, pos, end_pos + 3 };
    }
  }
  if (chars.size() and chars.front().ch == '=') {
    end_pos = chars.front().pos;
    chars.pop();
    return Token { Token::TokenName::AssignVar, text, pos, end_pos+1 };
  }
  return Token { Token::TokenName::Var, text, pos, end_pos+1 };
}

Token process_plus(std::queue<LexChar>& chars, int pos) {
  std::string text;
  int end_pos = pos;
  for (; chars.size() and chars.front().ch == '+'; chars.pop()) {
    text = text + chars.front().ch;
    end_pos = chars.front().pos;
  }
  return Token { Token::TokenName::Add, text, pos, end_pos+1 };
}

Token process_minus(std::queue<LexChar>& chars, int pos) {
  std::string text;
  int end_pos = pos;
  for (; chars.size() and chars.front().ch == '-'; chars.pop()) {
    text = text + chars.front().ch;
    end_pos = chars.front().pos;
  }
  return Token {
    text.length() % 2 ? Token::TokenName::Sub : Token::TokenName::Add,
    text,
    pos,
    end_pos+1
  };
}

Token process_star(std::queue<LexChar>& chars, int pos) {
  std::string text;
  int end_pos = pos;
  for (; chars.size() and chars.front().ch == '*'; chars.pop()) {
    text = text + chars.front().ch;
    end_pos = chars.front().pos;
  }
  if (text.length() > 2) {
    // TODO: error
  }
  return Token {
    text.length() % 2 ? Token::TokenName::Mul : Token::TokenName::Rtd,
    text,
    pos,
    end_pos+1
  };
}

Token process_slash(std::queue<LexChar>& chars, int pos) {
  std::string text;
  int end_pos = pos;
  for (; chars.size() and chars.front().ch == '/'; chars.pop()) {
    text = text + chars.front().ch;
    end_pos = chars.front().pos;
  }
  if (text.length() > 1) {
    // TODO: error
  }
  return Token { Token::TokenName::Div, text, pos, end_pos+1 };
}

Token process_obrac(std::queue<LexChar>& chars, int pos) {
  chars.pop();
  return Token { Token::TokenName::OBrac, "(", pos, pos + 1};
}

Token process_cbrac(std::queue<LexChar>& chars, int pos) {
  chars.pop();
  return Token { Token::TokenName::OBrac, ")", pos, pos + 1};
}

Token process_sq_brac(std::queue<LexChar>& chars, int pos) {
  std::string text;
  int end_pos = pos;
  chars.pop();
  do {
    text = text + chars.front().ch;
    chars.pop();
    end_pos = chars.front().pos;
  } while (chars.size() and chars.front().ch != ']');
  chars.pop();
  return Token { Token::TokenName::Fraction, text, pos, end_pos+1 };
}

std::vector<Token> lex(std::string& usr_expr) {
  std::vector<Token> tokens;
  std::queue<LexChar> chars = get_chars(usr_expr); 
  while (chars.size()) {
    Token tk;
    switch(chars.front().ch) {
    case ' ':
    case '\t':
    case '\n':
      chars.pop();
      continue;
    case '+': tk = process_plus(chars, chars.front().pos); break;
    case '-': tk = process_minus(chars, chars.front().pos); break;
    case '*': tk = process_star(chars, chars.front().pos); break;
    case '/': tk = process_slash(chars, chars.front().pos); break;
    case '(': tk = process_obrac(chars, chars.front().pos); break;
    case ')': tk = process_cbrac(chars, chars.front().pos); break;
    case '[': tk = process_sq_brac(chars, chars.front().pos); break;
    default: {
      if (isdigit(chars.front().ch)) {
        tk = process_digit(chars, chars.front().pos);
      }
      else if (isalpha(chars.front().ch)) {
        tk = process_symbols(chars, chars.front().pos);
      }
    } break;
    }
    tokens.push_back(tk);
  }
  return tokens;
}
