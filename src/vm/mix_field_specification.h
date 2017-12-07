#ifndef MIX_FIELD_SPECIFICATION_H
#define MIX_FIELD_SPECIFICATION_H

#include "mix_byte.h"

#include <iosfwd>

namespace mix {
struct FieldSpecification {
  static const FieldSpecification DEFAULT;
  static FieldSpecification decode(byte f);

  byte low;
  byte high;

  byte encode() const;

  void print(std::ostream &os) const;
};

std::ostream &operator<<(std::ostream &os, FieldSpecification fs);

} // namespace mix

#endif // MIX_FIELD_SPECIFICATION_H
