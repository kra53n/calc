#include <queue>
#include <vector>
#include <iostream>

#include "syntax/lex.hpp"
#include "syntax/parse.hpp"
#include "syntax/interp.hpp"

using namespace std;

int main() {
  //string usr_expr = "[1/2] + matrix(1) -1**2 + 123 + 3 * 321 * complex(1 3) + matrix((1 2) (2 1)) + 2 * (21 + 2)**2";
  std::string usr_expr;
  do {
    cout << "> ";
    getline(cin, usr_expr);
    vector<Token> tokens = lex(usr_expr);
    Calculatable* val = interp(parse(tokens));
    if (val) {
      cout << val->result() << endl;
    }
  } while(usr_expr != "0");
}
