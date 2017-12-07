#include "mix_field_specification.h"

#include <sstream>

namespace mix {

namespace {
const byte BASE = 8;
}

const FieldSpecification FieldSpecification::DEFAULT{0, 5};

FieldSpecification FieldSpecification::decode(byte f) {
  FieldSpecification fmt;
  fmt.low = f / BASE;
  fmt.high = f - fmt.low * BASE;
  return fmt;
}

byte FieldSpecification::encode() const {
  return low * BASE + high;
}

void FieldSpecification::print(std::ostream &os) const {
  os << "(" << static_cast<int>(low) << ":" << static_cast<int>(high) << ")";
}

std::ostream &operator<<(std::ostream &os, FieldSpecification fs) {
  fs.print(os);
  return os;
}

} // namespace mix
