#pragma once

#include <string>
#include <unordered_map>

#include "Parser.hpp"

namespace xml {

struct Result {
  struct _Data {
    std::string type;
    std::string val;
  };

  std::unordered_map<std::string, _Data> vars;
  std::string eval;
};

class Interp {
  Tag* root = nullptr;
  Result res;

  bool _wrong_structure();
  void _process_errors();

  void _interp_vars_tags();
  void _interp_eval_tag();
public:

  Interp(Tag* root);
  Result interp();
};

} // xml