#ifndef MIX_INSTRUCTION_H
#define MIX_INSTRUCTION_H

#include "mix_field_specification.h"
#include "mix_word.h"

#include <iosfwd>

namespace mix {

class Instruction {
public:
  explicit Instruction(const Word &word);

  short get_address() const;

  byte get_operation_code() const;
  FieldSpecification get_field_specification() const;
  byte get_modification() const;
  byte get_specification() const;

  void print(std::ostream &os, const char *command_name) const;

private:
  Word word;
};

} // namespace mix

#endif // MIX_INSTRUCTION_H
