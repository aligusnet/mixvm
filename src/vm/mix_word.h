#ifndef MIX_WORD_H
#define MIX_WORD_H

#include "format_range.h"
#include "mix_byte.h"

#include <iosfwd>

namespace mix {
const int DATA_BYTES_IN_WORD = 5;
const int VALUES_IN_WORD =
    VALUES_IN_BYTE * VALUES_IN_BYTE * VALUES_IN_BYTE * VALUES_IN_BYTE * VALUES_IN_BYTE; // DATA_BYTES_IN_WORD times

class Word {
public:
  static Word make_as_instruction(byte cmd, short addr = 0, byte i = 0, byte f = DEFAULT_FORMAT);

  Word() = default;
  Word(bool sign, byte a1, byte a2, byte i, byte f, byte c);

  short get_address() const;
  void set_address(short address);

  void right_shift(int nbytes);
  void left_shift(int nbytes);

  void set_value(const Word &source, int format);
  // return true if overflowed
  bool set_value(int value);

  value_type get_value(int format = DEFAULT_FORMAT) const;

  byte get_operation_code() const;
  byte get_modification() const;
  byte get_specification() const;

  bool get_sign() const;
  void set_sign(bool value);

  void print_word(std::ostream &os) const;
  void print_instruction(std::ostream &os, const char *command_name) const;

private:
  bool sign;
  byte bytes[DATA_BYTES_IN_WORD];

  friend struct LongValue;
};

Word make_cmd(byte cmd, short addr = 0, byte f = DEFAULT_FORMAT);

} // namespace mix

#endif // MIX_WORD_H
