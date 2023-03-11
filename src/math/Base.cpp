#include "Base.hpp"

std::ostream& operator<<(std::ostream& out, const Base& base) {
  out << base.result();
  return out;
}
