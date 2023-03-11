#pragma once

#include <string>

class Base {
public:
  virtual std::string result() const;
  friend std::ostream& operator<<(std::ostream& out, const Base& base);
};
