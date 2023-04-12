#include "Token.hpp"

namespace xml {

Token::Token(TokenName _name, const char* _lexeme, int _row, int _col)
  : name(_name)
  , lexeme(_lexeme)
  , row(_row)
  , col(_col)
{
}

} // xml
