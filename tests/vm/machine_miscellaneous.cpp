#include "machine_fixture.h"

namespace mix {
class MachineMiscellaneousTestSuite : public MachineFixture {
protected:
  void SetUp() override {
    machine.reg_a = default_reg_a;
    machine.reg_x = default_reg_x;
  }

  void expect_reg_x_unchanged() {
    expect_eq(default_reg_x, machine.reg_x);
  }

  big_register default_reg_a{Sign::Positive, 1, 2, 3, 4, 5};
  big_register default_reg_x{Sign::Negative, 6, 7, 8, 9, 10};
};

TEST_F(MachineMiscellaneousTestSuite, sla) {
  machine.sla(make_instruction(cmd_sla, 2));

  expect_eq(Word(Sign::Positive, 3, 4, 5, 0, 0), machine.reg_a);
  expect_reg_x_unchanged();
}

TEST_F(MachineMiscellaneousTestSuite, sla_to_huge_number_elements) {
  machine.sla(make_instruction(cmd_sla, 1000));

  expect_eq(Word(Sign::Positive, 0, 0, 0, 0, 0), machine.reg_a);
  expect_reg_x_unchanged();
}

TEST_F(MachineMiscellaneousTestSuite, sra) {
  machine.sra(make_instruction(cmd_sra, 2));

  expect_eq(Word(Sign::Positive, 0, 0, 1, 2, 3), machine.reg_a);
  expect_reg_x_unchanged();
}

TEST_F(MachineMiscellaneousTestSuite, sra_to_huge_number_elements) {
  machine.sra(make_instruction(cmd_sra, 512));

  expect_eq(Word(Sign::Positive, 0, 0, 0, 0, 0), machine.reg_a);
  expect_reg_x_unchanged();
}

TEST_F(MachineMiscellaneousTestSuite, slax) {
  machine.slax(make_instruction(cmd_slax, 3));

  expect_eq(Word(Sign::Positive, 4, 5, 6, 7, 8), machine.reg_a);
  expect_eq(Word(Sign::Negative, 9, 10, 0, 0, 0), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, slax_to_big_number_of_elements) {
  machine.slax(make_instruction(cmd_slax, 7));

  expect_eq(Word(Sign::Positive, 8, 9, 10, 0, 0), machine.reg_a);
  expect_eq(Word(Sign::Negative, 0, 0, 0, 0, 0), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, slax_to_huge_number_of_elements) {
  machine.slax(make_instruction(cmd_slax, 391));

  expect_eq(Word(Sign::Positive, 0, 0, 0, 0, 0), machine.reg_a);
  expect_eq(Word(Sign::Negative, 0, 0, 0, 0, 0), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, srax) {
  machine.srax(make_instruction(cmd_srax, 3));

  expect_eq(Word(Sign::Positive, 0, 0, 0, 1, 2), machine.reg_a);
  expect_eq(Word(Sign::Negative, 3, 4, 5, 6, 7), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, srax_to_big_number_of_elements) {
  machine.srax(make_instruction(cmd_srax, 7));

  expect_eq(Word(Sign::Positive, 0, 0, 0, 0, 0), machine.reg_a);
  expect_eq(Word(Sign::Negative, 0, 0, 1, 2, 3), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, srax_to_huge_number_of_elements) {
  machine.srax(make_instruction(cmd_srax, 711));

  expect_eq(Word(Sign::Positive, 0, 0, 0, 0, 0), machine.reg_a);
  expect_eq(Word(Sign::Negative, 0, 0, 0, 0, 0), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, slc) {
  machine.slc(make_instruction(cmd_slc, 4));

  expect_eq(Word(Sign::Positive, 5, 6, 7, 8, 9), machine.reg_a);
  expect_eq(Word(Sign::Negative, 10, 1, 2, 3, 4), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, slc_to_5) {
  machine.slc(make_instruction(cmd_slc, 5));

  expect_eq(Word(Sign::Positive, 6, 7, 8, 9, 10), machine.reg_a);
  expect_eq(Word(Sign::Negative, 1, 2, 3, 4, 5), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, slc_to_10) {
  machine.slc(make_instruction(cmd_slc, 10));

  expect_eq(default_reg_a, machine.reg_a);
  expect_eq(default_reg_x, machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, slc_to_7) {
  machine.slc(make_instruction(cmd_slc, 7));

  expect_eq(Word(Sign::Positive, 8, 9, 10, 1, 2), machine.reg_a);
  expect_eq(Word(Sign::Negative, 3, 4, 5, 6, 7), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, slc_to_107) {
  machine.slc(make_instruction(cmd_slc, 107));

  expect_eq(Word(Sign::Positive, 8, 9, 10, 1, 2), machine.reg_a);
  expect_eq(Word(Sign::Negative, 3, 4, 5, 6, 7), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, src) {
  machine.src(make_instruction(cmd_src, 4));

  expect_eq(Word(Sign::Positive, 7, 8, 9, 10, 1), machine.reg_a);
  expect_eq(Word(Sign::Negative, 2, 3, 4, 5, 6), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, src_to_5) {
  machine.src(make_instruction(cmd_src, 5));

  expect_eq(Word(Sign::Positive, 6, 7, 8, 9, 10), machine.reg_a);
  expect_eq(Word(Sign::Negative, 1, 2, 3, 4, 5), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, src_to_10) {
  machine.src(make_instruction(cmd_src, 10));

  expect_eq(default_reg_a, machine.reg_a);
  expect_eq(default_reg_x, machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, src_to_7) {
  machine.src(make_instruction(cmd_src, 7));

  expect_eq(Word(Sign::Positive, 4, 5, 6, 7, 8), machine.reg_a);
  expect_eq(Word(Sign::Negative, 9, 10, 1, 2, 3), machine.reg_x);
}

TEST_F(MachineMiscellaneousTestSuite, src_to_107) {
  machine.src(make_instruction(cmd_src, 107));

  expect_eq(Word(Sign::Positive, 4, 5, 6, 7, 8), machine.reg_a);
  expect_eq(Word(Sign::Negative, 9, 10, 1, 2, 3), machine.reg_x);
}

} // namespace mix
