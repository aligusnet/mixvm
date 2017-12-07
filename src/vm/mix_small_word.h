#ifndef MIX_SMALL_REGISTER_H
#define MIX_SMALL_REGISTER_H

#include "mix_byte.h"
#include "mix_field_specification.h"
#include "mix_generic_word.h"
#include "mix_sign.h"

#include <iosfwd>

namespace mix {

class SmallWord : public GenericWord<2> {
public:
  bool inc();  // return true if overflowed
};

} // namespace mix

#endif // MIX_SMALL_REGISTER_H
