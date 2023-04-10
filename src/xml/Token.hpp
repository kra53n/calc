#pragma once

#include <string>

namespace xml {

struct Token {
  enum class TokenName {
    OBrac, // <
    CBrac, // >
    TagName,
    Elem, // <tag_name>some elem</tag_name>
          //           ~~~~~~~~~ - Elem
    AttrName, // <tag_name attr1="some info"         attr2="another info"></tag_name>
              //           ~~~~~ - Attribute names - ~~~~~
    AttrVal, // <tag_name attr1="some info"                    attr2='another info'></tag_name>
             //                  ~~~~~~~~~ - Attribute values -       ~~~~~~~~~~~~
  };

  int row;
  std::string text;
};

} // xml
