
#include <gtest/gtest.h>

#include <vm/mix_generic_word.h>

namespace mix {

TEST(GenericWordTestSuite, set_positive_address) {
  GenericWord<5> word;
  word.set_address(70);

  EXPECT_EQ(1, word.bytes[0]);
  EXPECT_EQ(6, word.bytes[1]);
  EXPECT_EQ(Sign::Positive, word.sign);
}

TEST(GenericWordTestSuite, set_negative_address) {
  GenericWord<5> word;
  word.set_address(-71);

  EXPECT_EQ(1, word.bytes[0]);
  EXPECT_EQ(7, word.bytes[1]);
  EXPECT_EQ(Sign::Negative, word.sign);
}

TEST(GenericWordTestSuite, get_positive_address) {
  GenericWord<5> word;
  word.bytes[0] = 1;
  word.bytes[1] = 6;
  word.sign = Sign::Positive;

  EXPECT_EQ(70, word.get_address());
}

TEST(GenericWordTestSuite, get_negative_address) {
  GenericWord<5> word;
  word.bytes[0] = 1;
  word.bytes[1] = 7;
  word.sign = Sign::Negative;

  EXPECT_EQ(-71, word.get_address());
}

} // namespace mix
