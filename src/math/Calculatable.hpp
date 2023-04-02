#pragma once

#include <string>

#include "../syntax/Token.hpp"

class Calculatable {
protected:
  Token::TokenName token_name;
public:
  bool is_var = false;

  friend std::ostream& operator<<(std::ostream& out, const Calculatable& calculatable);
  Token::TokenName get_token_name();

  virtual std::string result() const = 0;
  virtual Calculatable* copy() const = 0;
  virtual Calculatable* add(Calculatable* other) = 0;
  virtual Calculatable* sub(Calculatable* other) = 0;
  virtual Calculatable* mul(Calculatable* other) = 0;
  virtual Calculatable* div(Calculatable* other) = 0;
  virtual Calculatable* rtd(Calculatable* other) = 0;
};
