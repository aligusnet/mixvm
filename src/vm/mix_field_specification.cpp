#include "mix_field_specification.h"

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

} // namespace mix
