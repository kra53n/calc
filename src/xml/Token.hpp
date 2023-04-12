#pragma once

#include <string>

// TODO: replace `const char*` to `std::string`

namespace xml {

struct Token {
  enum class TokenName {
    OBrac, // <
    CBrac, // >
    OBracWithSlash, // </

    TagName,
    Elem, // <tag_name>some elem</tag_name>
          //           ~~~~~~~~~ - Elem
    AttrName, // <tag_name attr1="some info"         attr2="another info"></tag_name>
              //           ~~~~~ - Attribute names - ~~~~~
    AttrVal, // <tag_name attr1="some info"                    attr2='another info'></tag_name>
             //                  ~~~~~~~~~ - Attribute values -       ~~~~~~~~~~~~
  };

  TokenName name; 
  const char* lexeme;
  int row;
  int col; // where lexeme begins

  Token(TokenName _name, const char* _lexeme, int _row, int _col);
};

} // xml
