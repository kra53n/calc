#include "xml_Error.hpp"
#include "xml_Interp.hpp"
#include "../util.hpp"

namespace xml {

Interp::Interp(Tag* root) 
  : root(root)
{
}

bool Interp::_wrong_structure() {
  if (
    root->tags.size() < 2 or
    root->tags[0]->name != "vars"
  ) {
    return true;
  }

  bool was_eval = false;
  for (Tag* tag : root->tags) {
    if (tag->name == "vars") {
      continue;
    }
    else if (tag->name == "eval") {
      if (was_eval) {
        return true;
      }
      was_eval = true;
    }
    else {
      return true;
    }
  }

  return false;
}

void Interp::_process_errors() {
  if (root == nullptr) {
    throw Error("file without any tags");
  }
  if (root->name != "calc") {
    throw Error("file must begin with calc, " + root->name + " was given");
  }

  if (_wrong_structure()) {
    throw Error("file must contain `vars`, `eval` tags");
  }
}

void Interp::_interp_vars_tags() {
  for (int i = 0; root->tags[i]->name == "vars"; i++) {
    std::string var_type = root->tags[i]->attrs[0].val;
    for (Tag* tag : root->tags[i]->tags) {
      std::string var_name = tag->attrs[0].val;
      std::string var_val = tag->val->substr(0, tag->val->length());
      res.vars.insert({ var_name, Content::_Data { var_type, var_val }});
    }
  }
}

void Interp::_interp_eval_tag() {
  int eval_idx = root->tags.size() - 1;

  std::string buf = root->tags[eval_idx]->val->substr(0, root->tags[eval_idx]->val->length());
  std::string line;
  for (char ch : buf) {
    if (is_skip_char(ch)) {
      if (ch == '\n') {
        if (line.size()) {
          res.eval.push_back(line);
        }
        line.clear();
      }
      continue;
    }
    line = line + ch;
  }
  if (buf[buf.length() - 1] != '\n') {
		res.eval.push_back(line);
  }
}

Content Interp::interp() {
  _process_errors();

  _interp_vars_tags();
  _interp_eval_tag();

  return res;
}

} // xml