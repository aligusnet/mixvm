#ifndef MIX_SMALL_REGISTER_H
#define MIX_SMALL_REGISTER_H

#include "mix_byte.h"
#include "mix_field_specification.h"

#include <iosfwd>

namespace mix {
const int DATA_BYTES_IN_SMALL_REGISTER = 2;

class SmallWord {
public:
  bool inc();  // return true if overflowed
  bool set_value(value_type val);  // return true if overflowed
  void set_address(short addr);

  int get_value(FieldSpecification format = FieldSpecification::DEFAULT) const;

  bool get_sign() const;
  void set_sign(bool sign);
  
  void print(std::ostream &os) const;
  
private:
  bool sign;
  byte bytes[DATA_BYTES_IN_SMALL_REGISTER];
};

} // namespace mix

#endif // MIX_SMALL_REGISTER_H
