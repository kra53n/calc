#include "lib.hpp"

void repl() {
  std::string usr_expr;
  std::unordered_map<std::string, Calculable*> vars;
  do {
    cout << "> ";
    getline(cin, usr_expr);
    list<Token> tokens = lex(usr_expr);
    try {
      Calculable* val = interp(vars, parse(tokens));
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

void process_xml(std::string filename) {
  xml::Content content = xml::get_content(filename);
  std::unordered_map<std::string, Calculable*> vars;
  for (auto var : content.vars) {
    auto s = var.first;
    list<Token> tokens = lex(var.second.val);
    if (tokens.size() != 1) {
      throw xml::Error("mistake in type declaration");
    }
    std::string val = tokens.front().text;
    vars.insert({ var.first, get_type_by_name_and_val(var.second.type, val) });
  }
  for (std::string it : content.eval) {
    try {
      Calculable* val = interp(vars, parse(lex(it)));
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
  }
}