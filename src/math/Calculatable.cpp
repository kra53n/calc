#include "Calculatable.hpp"

std::ostream& operator<<(std::ostream& out, const Calculatable& calculatable) {
  out << calculatable.result();
  return out;
}
