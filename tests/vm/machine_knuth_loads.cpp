
#include "machine_fixture.h"

namespace mix {
class MachineKnuthLoadsTestSuite : public MachineFixture {
protected:
  int address;

  MachineKnuthLoadsTestSuite() {
    address = 2000;
    machine.memory[address] = Word(NEG_SIGN, 8, 1, 3, 5, 4);
  }

  void expect_reg_a(Word expected) const {
    expect_eq(expected, machine.reg_a);
  }

  void expect_reg_x(Word expected) const {
    expect_eq(expected, machine.reg_x);
  }

  void execute_lda() {
    machine.lda(make_cmd(cmd_lda, address));
  }

  void execute_lda(byte format_low, byte format_high) {
    machine.lda(make_cmd(cmd_lda, address, {format_low, format_high}));
  }

  void execute_ldx() {
    machine.ldx(make_cmd(cmd_ldx, address));
  }

  void execute_ldx(byte format_low, byte format_high) {
    machine.ldx(make_cmd(cmd_ldx, address, {format_low, format_high}));
  }
};

TEST_F(MachineKnuthLoadsTestSuite, lda_normal) {
  execute_lda();
  expect_reg_a(Word(NEG_SIGN, 8, 1, 3, 5, 4));
}

TEST_F(MachineKnuthLoadsTestSuite, lda_1_5_bytes) {
  execute_lda(1, 5);
  expect_reg_a(Word(POS_SIGN, 8, 1, 3, 5, 4));
}

TEST_F(MachineKnuthLoadsTestSuite, lda_3_5_bytes) {
  execute_lda(3, 5);
  expect_reg_a(Word(POS_SIGN, 0, 0, 3, 5, 4));
}

TEST_F(MachineKnuthLoadsTestSuite, lda_0_3_bytes) {
  execute_lda(0, 3);
  expect_reg_a(Word(NEG_SIGN, 0, 0, 8, 1, 3));
}

TEST_F(MachineKnuthLoadsTestSuite, lda_4_4_bytes) {
  execute_lda(4, 4);
  expect_reg_a(Word(POS_SIGN, 0, 0, 0, 0, 5));
}

TEST_F(MachineKnuthLoadsTestSuite, lda_0_0_bytes) {
  execute_lda(0, 0);
  expect_reg_a(Word(NEG_SIGN, 0, 0, 0, 0, 0));
}

TEST_F(MachineKnuthLoadsTestSuite, lda_1_1_bytes) {
  execute_lda(1, 1);
  expect_reg_a(Word(POS_SIGN, 0, 0, 0, 0, 8));
}

TEST_F(MachineKnuthLoadsTestSuite, ldx_normal) {
  execute_ldx();
  expect_reg_x(Word(NEG_SIGN, 8, 1, 3, 5, 4));
}

TEST_F(MachineKnuthLoadsTestSuite, ldx_1_5_bytes) {
  execute_ldx(1, 5);
  expect_reg_x(Word(POS_SIGN, 8, 1, 3, 5, 4));
}

TEST_F(MachineKnuthLoadsTestSuite, ldx_3_5_bytes) {
  execute_ldx(3, 5);
  expect_reg_x(Word(POS_SIGN, 0, 0, 3, 5, 4));
}

TEST_F(MachineKnuthLoadsTestSuite, ldx_0_3_bytes) {
  execute_ldx(0, 3);
  expect_reg_x(Word(NEG_SIGN, 0, 0, 8, 1, 3));
}

TEST_F(MachineKnuthLoadsTestSuite, ldx_4_4_bytes) {
  execute_ldx(4, 4);
  expect_reg_x(Word(POS_SIGN, 0, 0, 0, 0, 5));
}

TEST_F(MachineKnuthLoadsTestSuite, ldx_0_0_bytes) {
  execute_ldx(0, 0);
  expect_reg_x(Word(NEG_SIGN, 0, 0, 0, 0, 0));
}

TEST_F(MachineKnuthLoadsTestSuite, ldx_1_1_bytes) {
  execute_ldx(1, 1);
  expect_reg_x(Word(POS_SIGN, 0, 0, 0, 0, 8));
}

} // namespace mix
