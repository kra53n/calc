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
  xml::Content content;

  try {
		content = xml::get_content(filename);
  }
  catch (xml::Error e) {
    cout << e;
  }

  std::unordered_map<std::string, Calculable*> vars;
  for (auto var : content.vars) {
    auto s = var.first;
    list<Token> tokens;
    try {
			tokens = lex(var.second.val);
			std::string val = tokens.front().text;
			vars.insert({ var.first, get_type_by_name_and_val(var.second.type, val) });
    }
    catch (UnderliningError e) {
      cout << e;
      exit(1);
    }
    catch (...) {
      cout << "Something went wrong ¯\\_(ツ)_/¯" << endl;
      exit(1);
    }
    if (tokens.size() != 1) {
      throw xml::Error("mistake in type declaration");
    }
  }
  for (std::string it : content.eval) {
    int code_error = 1;
    try {
      Calculable* val = interp(vars, parse(lex(it)));
      if (val) {
        cout << val->result() << endl;
      }
    }
    catch (UnderliningError e) {
      cout << e;
      exit(code_error);
    }
    catch (...) {
      cout << "Something went wrong ¯\\_(ツ)_/¯" << endl;
      exit(code_error);
    }
  }
}