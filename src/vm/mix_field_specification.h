#ifndef MIX_FIELD_SPECIFICATION_H
#define MIX_FIELD_SPECIFICATION_H

#include "mix_byte.h"

namespace mix {
struct FieldSpecification {
  static const FieldSpecification DEFAULT;
  static FieldSpecification decode(byte f);

  byte low;
  byte high;

  byte encode() const;
};

} // namespace mix

#endif // MIX_FIELD_SPECIFICATION_H
