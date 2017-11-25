
#include "machine_fixture.h"

namespace mix {
class MachineKnuthStoresTestSuite : public MachineFixture {
protected:
  int address;

  MachineKnuthStoresTestSuite() {
    address = 2000;
    machine.reg_a = Word(POS_SIGN, 6, 7, 8, 9, 0);
    machine.reg_x = Word(POS_SIGN, 16, 17, 18, 19, 20);
    machine.memory[address] = Word(NEG_SIGN, 1, 2, 3, 4, 5);
  }

  void expect_memory(Word expected) const {
    expect_eq(expected, machine.memory[address]);
  }

  void execute_sta() {
    machine.sta(make_cmd(cmd_sta, address));
  }

  void execute_sta(byte format_low, byte format_high) {
    machine.sta(make_cmd(cmd_sta, address, {format_low, format_high}));
  }

  void execute_stx() {
    machine.stx(make_cmd(cmd_stx, address));
  }

  void execute_stx(byte format_low, byte format_high) {
    machine.stx(make_cmd(cmd_stx, address, {format_low, format_high}));
  }
};

TEST_F(MachineKnuthStoresTestSuite, sta_normal) {
  execute_sta();
  expect_memory(Word(POS_SIGN, 6, 7, 8, 9, 0));
}

TEST_F(MachineKnuthStoresTestSuite, sta_1_5_bytes) {
  execute_sta(1, 5);
  expect_memory(Word(NEG_SIGN, 6, 7, 8, 9, 0));
}

TEST_F(MachineKnuthStoresTestSuite, sta_5_5_bytes) {
  execute_sta(5, 5);
  expect_memory(Word(NEG_SIGN, 1, 2, 3, 4, 0));
}

TEST_F(MachineKnuthStoresTestSuite, sta_2_2_bytes) {
  execute_sta(2, 2);
  expect_memory(Word(NEG_SIGN, 1, 0, 3, 4, 5));
}

TEST_F(MachineKnuthStoresTestSuite, sta_2_3_bytes) {
  execute_sta(2, 3);
  expect_memory(Word(NEG_SIGN, 1, 9, 0, 4, 5));
}

TEST_F(MachineKnuthStoresTestSuite, sta_0_1_bytes) {
  execute_sta(0, 1);
  expect_memory(Word(POS_SIGN, 0, 2, 3, 4, 5));
}

TEST_F(MachineKnuthStoresTestSuite, stx_normal) {
  execute_stx();
  expect_memory(Word(POS_SIGN, 16, 17, 18, 19, 20));
}

TEST_F(MachineKnuthStoresTestSuite, stx_1_5_bytes) {
  execute_stx(1, 5);
  expect_memory(Word(NEG_SIGN, 16, 17, 18, 19, 20));
}

TEST_F(MachineKnuthStoresTestSuite, stx_5_5_bytes) {
  execute_stx(5, 5);
  expect_memory(Word(NEG_SIGN, 1, 2, 3, 4, 20));
}

TEST_F(MachineKnuthStoresTestSuite, stx_2_2_bytes) {
  execute_stx(2, 2);
  expect_memory(Word(NEG_SIGN, 1, 20, 3, 4, 5));
}

TEST_F(MachineKnuthStoresTestSuite, stx_2_3_bytes) {
  execute_stx(2, 3);
  expect_memory(Word(NEG_SIGN, 1, 19, 20, 4, 5));
}

TEST_F(MachineKnuthStoresTestSuite, stx_0_1_bytes) {
  execute_stx(0, 1);
  expect_memory(Word(POS_SIGN, 20, 2, 3, 4, 5));
}

} // namespace mix
