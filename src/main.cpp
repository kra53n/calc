#include <queue>
#include <vector>
#include <iostream>

#include "errors.hpp"
#include "syntax/lex.hpp"
#include "syntax/parse.hpp"
#include "syntax/interp.hpp"

using namespace std;

int main() {
  std::string usr_expr;
  do {
    cout << "> ";
    getline(cin, usr_expr);
    list<Token> tokens = lex(usr_expr);
    try {
      Calculatable* val = interp(parse(tokens));
      if (val) {
        cout << val->result() << endl;
      }
    }
    catch (UnderliningError e) {
      cout << e;
    }
    catch (...) {
      cout << "Something went wrong ¯\\_(ツ)_/¯" << endl;
    }
  } while(usr_expr != "q");
}
