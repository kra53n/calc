#pragma once

#include <string>

namespace xml {

struct Token {
  enum class TokenName {
    OBrac, // <
    CBrac, // >
    OBracWithSlash, // </

    TagName,
    Val, // <tag_name>some elem</tag_name>
         //           ~~~~~~~~~ - Val
    Attr, // <tag_name attr1="some info"               attr2></tag_name>
          //           ~~~~~~~~~~~~~~~~ - Attributes - ~~~~~
  };

  TokenName name; 
  std::string lexeme;
  int row;
  int col; // which character in the string does the token begin with

  Token(TokenName name, std::string lexeme, int row, int col);
};

} // xml
