#include <gtest/gtest.h>

#include <vm/mix_field_specification.h>

namespace mix {
class FieldSpecificationTestSuite : public ::testing::Test {
protected:
  FieldSpecification sign_only{0, 0};
  byte sign_only_encoded{0};

  FieldSpecification sign_and_first_two_bytes{0, 2};
  byte sign_and_first_two_bytes_encoded{2};

  FieldSpecification whole_word{0, 5};
  byte whole_word_encoded{5};

  FieldSpecification whole_word_except_for_sign{1, 5};
  byte whole_word_except_for_sign_encoded{13};

  FieldSpecification fourth_byte_only{4, 4};
  byte fourth_byte_only_encoded{36};

  FieldSpecification two_least_signicant_bytes{4, 5};
  byte two_least_signicant_bytes_encoded{37};
};

bool operator==(const FieldSpecification &lhs, const FieldSpecification &rhs) {
  return lhs.low == rhs.low && lhs.high == rhs.high;
}

TEST_F(FieldSpecificationTestSuite, decode_sign_only) {
  EXPECT_EQ(sign_only, FieldSpecification::decode(sign_only_encoded));
}

TEST_F(FieldSpecificationTestSuite, encode_sign_only) {
  EXPECT_EQ(sign_only_encoded, sign_only.encode());
}

TEST_F(FieldSpecificationTestSuite, decode_sign_and_first_two_bytes) {
  EXPECT_EQ(sign_and_first_two_bytes, FieldSpecification::decode(sign_and_first_two_bytes_encoded));
}

TEST_F(FieldSpecificationTestSuite, encode_sign_and_first_two_bytes) {
  EXPECT_EQ(sign_and_first_two_bytes_encoded, sign_and_first_two_bytes.encode());
}

TEST_F(FieldSpecificationTestSuite, decode_whole_word) {
  EXPECT_EQ(whole_word, FieldSpecification::decode(whole_word_encoded));
}

TEST_F(FieldSpecificationTestSuite, encode_whole_word) {
  EXPECT_EQ(whole_word_encoded, whole_word.encode());
}

TEST_F(FieldSpecificationTestSuite, decode_whole_word_except_for_sign) {
  EXPECT_EQ(whole_word_except_for_sign, FieldSpecification::decode(whole_word_except_for_sign_encoded));
}

TEST_F(FieldSpecificationTestSuite, encode_whole_word_except_for_sign) {
  EXPECT_EQ(whole_word_except_for_sign_encoded, whole_word_except_for_sign.encode());
}

TEST_F(FieldSpecificationTestSuite, decode_fourth_byte_only) {
  EXPECT_EQ(fourth_byte_only, FieldSpecification::decode(fourth_byte_only_encoded));
}

TEST_F(FieldSpecificationTestSuite, encode_fourth_byte_only) {
  EXPECT_EQ(fourth_byte_only_encoded, fourth_byte_only.encode());
}

TEST_F(FieldSpecificationTestSuite, decode_two_least_signicant_bytes) {
  EXPECT_EQ(two_least_signicant_bytes, FieldSpecification::decode(two_least_signicant_bytes_encoded));
}

TEST_F(FieldSpecificationTestSuite, encode_two_least_signicant_bytes) {
  EXPECT_EQ(two_least_signicant_bytes_encoded, two_least_signicant_bytes.encode());
}
} // namespace mix
