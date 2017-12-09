#ifndef MIX_WORD_H
#define MIX_WORD_H

#include "mix_byte.h"
#include "mix_field_specification.h"
#include "mix_generic_word.h"

namespace mix {
class Word : public GenericWord<5> {
public:
  Word() = default;
  Word(Sign sign, byte a1, byte a2, byte i, byte f, byte c);
};

} // namespace mix

#endif // MIX_WORD_H
