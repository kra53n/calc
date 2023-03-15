#pragma once

#include <stack>
#include <vector>
#include <string>
#include <unordered_map>

#include "Token.hpp"

const std::unordered_map<std::string, Token::TokenName> _token_name_by_string = {
  { "complex", Token::TokenName::Cx },
  { "cx", Token::TokenName::Cx },
  { "matrix", Token::TokenName::Mx },
  { "mx", Token::TokenName::Mx },
};

std::vector<Token> lex(std::string usr_expr);
