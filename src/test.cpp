#include <queue>
#include <vector>
#include <iostream>

#include "syntax/lex.hpp"
#include "syntax/parse.hpp"
#include "syntax/interp.hpp"

using namespace std;

int main() {
  //string usr_expr = "[1/2] + matrix(1) -1**2 + 123 + 3 * 321 * complex(1 3) + matrix((1 2) (2 1)) + 2 * (21 + 2)**2";
  string usr_expr = "2 + 5*6 + (2-9) + 2**2";
  vector<Token> tokens = lex(usr_expr);
  for (Token token : tokens) {
    cout << token << endl;
  }

  cout << interp(parse(tokens))->result() << endl;
}
