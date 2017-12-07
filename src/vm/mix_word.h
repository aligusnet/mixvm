#ifndef MIX_WORD_H
#define MIX_WORD_H

#include "mix_byte.h"
#include "mix_field_specification.h"
#include "mix_generic_word.h"

namespace mix {
class Word : public GenericWord<5> {
public:
  static Word make_as_instruction(byte cmd, short addr = 0, byte i = 0,
                                  FieldSpecification f = FieldSpecification::DEFAULT);

  Word() = default;
  Word(Sign sign, byte a1, byte a2, byte i, byte f, byte c);
};

enum bytes_format { byte_a1 = 0, byte_a2 = 1, byte_i = 2, byte_f = 3, byte_c = 4 };

} // namespace mix

#endif // MIX_WORD_H
