#include "Token.hpp"

namespace xml {

Token::Token(TokenName name, std::string lexeme, int row, int col)
  : name(name)
  , lexeme(lexeme)
  , row(row)
  , col(col)
{
}

} // xml
