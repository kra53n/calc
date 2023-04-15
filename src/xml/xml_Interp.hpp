#pragma once

#include <string>
#include <unordered_map>

#include "xml_Parser.hpp"

namespace xml {

struct Content {
  struct _Data {
    std::string type;
    std::string val;
  };

  std::unordered_map<std::string, _Data> vars;
  std::vector<std::string> eval;
};

class Interp {
  Tag* root = nullptr;
  Content res;

  bool _wrong_structure();
  void _process_errors();

  void _interp_vars_tags();
  void _interp_eval_tag();
public:

  Interp(Tag* root);
  Content interp();
};

} // xml