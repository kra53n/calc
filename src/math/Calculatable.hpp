#pragma once

#include <string>

#include "../syntax/Token.hpp"

class Calculatable {
protected:
  Token::TokenName token_name;
public:
  friend std::ostream& operator<<(std::ostream& out, const Calculatable& calculatable);
  Token::TokenName get_token_name();

  virtual std::string result() const = 0;
  virtual Calculatable* add(Calculatable* other) = 0;
};
