#pragma once

#include <string>

#include "../syntax/Token.hpp"

class Calculable {
protected:
  Token::TokenName token_name;
public:
  bool is_var = false;
  bool free_up_memory = false;

  friend std::ostream& operator<<(std::ostream& out, const Calculable& Calculable);
  Token::TokenName get_token_name();

  virtual std::string result() const = 0;
  virtual Calculable* copy() const = 0;
  virtual Calculable* add(Calculable* other) = 0;
  virtual Calculable* sub(Calculable* other) = 0;
  virtual Calculable* mul(Calculable* other) = 0;
  virtual Calculable* div(Calculable* other) = 0;
  virtual Calculable* rtd(Calculable* other) = 0;
};
