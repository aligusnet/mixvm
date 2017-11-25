#include <fstream>
#include <iostream>

#include "vm/mix_machine.h"

void test_vm() {
  using namespace mix;
  std::ofstream ofs_start("start.txt");
  std::ofstream ofs_result1("result1.txt");
  std::ofstream ofs_result2("result2.txt");
  Machine vm;

  vm.memory[0] = make_cmd(cmd_lda, 152);
  vm.memory[1] = make_cmd(cmd_ldx, 150, encode_format(0, 3));
  vm.memory[2] = make_cmd(cmd_ld1, 151);
  vm.memory[3] = make_cmd(cmd_ld2, 151);
  vm.memory[4] = make_cmd(cmd_ld3, 151);
  vm.memory[5] = make_cmd(cmd_ld4, 151);
  vm.memory[6] = make_cmd(cmd_ld5, 151);
  vm.memory[7] = make_cmd(cmd_ld6, 151);
  vm.memory[8] = make_cmd(cmd_nop);
  vm.memory[9] = make_cmd(cmd_sta, 100);
  vm.memory[10] = make_cmd(cmd_sta, 101, encode_format(1, 5));
  vm.memory[11] = make_cmd(cmd_sta, 102, encode_format(5, 5));
  vm.memory[12] = make_cmd(cmd_sta, 103, encode_format(2, 2));
  vm.memory[13] = make_cmd(cmd_sta, 104, encode_format(2, 3));
  vm.memory[14] = make_cmd(cmd_sta, 105, encode_format(0, 1));
  vm.memory[15] = make_cmd(cmd_stx, 106, encode_format(3, 4));
  vm.memory[16] = make_cmd(cmd_stz, 107, encode_format(3, 4));
  vm.memory[17] = make_cmd(cmd_st1, 108);
  vm.memory[18] = make_cmd(cmd_st2, 109);
  vm.memory[19] = make_cmd(cmd_st3, 110);
  vm.memory[20] = make_cmd(cmd_st4, 111);
  vm.memory[21] = make_cmd(cmd_st5, 112);
  vm.memory[22] = make_cmd(cmd_st6, 113);
  vm.memory[23] = make_cmd(cmd_stj, 114);

  // add
  vm.memory[24] = make_cmd(cmd_sta, 199);
  vm.memory[25] = make_cmd(cmd_lda, 200);
  vm.memory[26] = make_cmd(cmd_sta, 201);
  vm.memory[27] = make_cmd(cmd_lda, 201, encode_format(5, 5));
  vm.memory[28] = make_cmd(cmd_add, 201, encode_format(4, 4));
  vm.memory[29] = make_cmd(cmd_add, 201, encode_format(3, 3));
  vm.memory[30] = make_cmd(cmd_add, 201, encode_format(2, 2));
  vm.memory[31] = make_cmd(cmd_add, 201, encode_format(1, 1));
  vm.memory[32] = make_cmd(cmd_sta, 202);

  // sub
  vm.memory[33] = make_cmd(cmd_lda, 210);
  vm.memory[34] = make_cmd(cmd_sub, 211);
  vm.memory[35] = make_cmd(cmd_sta, 212);

  vm.memory[36] = make_cmd(cmd_lda, 199);

  // mul
  vm.memory[38] = make_cmd(cmd_sta, 218);
  vm.memory[39] = make_cmd(cmd_stx, 219);
  vm.memory[40] = make_cmd(cmd_lda, 220); // A
  vm.memory[41] = make_cmd(cmd_mul, 221); //*B
  vm.memory[42] = make_cmd(cmd_sta, 222);
  vm.memory[43] = make_cmd(cmd_stx, 223);
  vm.memory[44] = make_cmd(cmd_lda, 218);
  vm.memory[45] = make_cmd(cmd_ldx, 219);

  // div
  vm.memory[46] = make_cmd(cmd_sta, 228);
  vm.memory[47] = make_cmd(cmd_stx, 229);
  vm.memory[48] = make_cmd(cmd_lda, 230);
  vm.memory[49] = make_cmd(cmd_ldx, 231);
  vm.memory[50] = make_cmd(cmd_div, 232);
  vm.memory[51] = make_cmd(cmd_sta, 233);
  vm.memory[52] = make_cmd(cmd_stx, 234);
  vm.memory[53] = make_cmd(cmd_lda, 228);
  vm.memory[54] = make_cmd(cmd_ldx, 229);

  vm.memory[55] = make_cmd(cmd_enta, 12, 2);
  vm.memory[56] = make_cmd(cmd_entx, 15, 2);
  vm.memory[57] = make_cmd(cmd_ent1, 1, 2);
  vm.memory[58] = make_cmd(cmd_ent2, 2, 2);
  vm.memory[59] = make_cmd(cmd_ent3, 3, 2);
  vm.memory[60] = make_cmd(cmd_ent4, 4, 2);
  vm.memory[61] = make_cmd(cmd_ent5, 5, 2);
  vm.memory[62] = make_cmd(cmd_ent6, 6, 2);

  vm.memory[63] = make_cmd(cmd_enna, 12, 3);
  vm.memory[64] = make_cmd(cmd_ennx, 15, 3);
  vm.memory[65] = make_cmd(cmd_enn1, 1, 3);
  vm.memory[66] = make_cmd(cmd_enn2, 2, 3);
  vm.memory[67] = make_cmd(cmd_enn3, 3, 3);
  vm.memory[68] = make_cmd(cmd_enn4, 4, 3);
  vm.memory[69] = make_cmd(cmd_enn5, 5, 3);
  vm.memory[70] = make_cmd(cmd_enn6, 6, 3);
  vm.memory[71] = make_cmd(cmd_cmpa, 150);
  vm.memory[72] = make_cmd(cmd_cmp1, 1500);
  vm.memory[73] = make_cmd(cmd_cmpx, 104);
  vm.memory[74] = make_cmd(cmd_jmp, 76, 0); // jmp
  vm.memory[75] = make_cmd(cmd_nop);
  // vm.memory[76] = make_cmd(	cmd_jmp, 74, 7); //jge
  vm.memory[76] = make_cmd(cmd_jmp, 74, 2); // jov

  // jump reg_a
  vm.memory[77] = make_cmd(cmd_ja, 82, 1); // jaz
  vm.memory[78] = make_cmd(cmd_ja, 80, 4); // janz
  vm.memory[79] = make_cmd(cmd_nop);
  vm.memory[80] = make_cmd(cmd_lda, 2000);
  vm.memory[81] = make_cmd(cmd_ja, 77, 3); // jann

  // jump reg_x
  vm.memory[82] = make_cmd(cmd_jx, 87, 1); // jxz
  vm.memory[83] = make_cmd(cmd_jx, 85, 4); // jxnz
  vm.memory[84] = make_cmd(cmd_nop);
  vm.memory[85] = make_cmd(cmd_ldx, 2000);
  vm.memory[86] = make_cmd(cmd_jx, 82, 3); // jxnn

  // jump reg_i1
  vm.memory[87] = make_cmd(cmd_j1, 92, 1); // j1z
  vm.memory[88] = make_cmd(cmd_j1, 90, 4); // j1nz
  vm.memory[89] = make_cmd(cmd_nop);
  vm.memory[90] = make_cmd(cmd_ld1, 2000);
  vm.memory[91] = make_cmd(cmd_j1, 87, 3); // j1nn

  // jump reg_i2
  vm.memory[87] = make_cmd(cmd_j2, 92, 1); // j2z
  vm.memory[88] = make_cmd(cmd_j2, 90, 4); // j2nz
  vm.memory[89] = make_cmd(cmd_nop);
  vm.memory[90] = make_cmd(cmd_ld2, 2000);
  vm.memory[91] = make_cmd(cmd_j2, 87, 3); // j2nn

  // jump reg_i3
  vm.memory[87] = make_cmd(cmd_j3, 92, 1); // j3z
  vm.memory[88] = make_cmd(cmd_j3, 90, 4); // j3nz
  vm.memory[89] = make_cmd(cmd_nop);
  vm.memory[90] = make_cmd(cmd_ld3, 2000);
  vm.memory[91] = make_cmd(cmd_j3, 87, 3); // j3nn

  // jump reg_i4
  vm.memory[87] = make_cmd(cmd_j4, 92, 1); // j4z
  vm.memory[88] = make_cmd(cmd_j4, 90, 4); // j4nz
  vm.memory[89] = make_cmd(cmd_nop);
  vm.memory[90] = make_cmd(cmd_ld4, 2000);
  vm.memory[91] = make_cmd(cmd_j4, 87, 3); // j4nn

  // jump reg_i5
  vm.memory[87] = make_cmd(cmd_j5, 92, 1); // j5z
  vm.memory[88] = make_cmd(cmd_j5, 90, 4); // j5nz
  vm.memory[89] = make_cmd(cmd_nop);
  vm.memory[90] = make_cmd(cmd_ld5, 2000);
  vm.memory[91] = make_cmd(cmd_j5, 87, 3); // j5nn

  // jump reg_i6
  vm.memory[87] = make_cmd(cmd_j6, 92, 1); // j6z
  vm.memory[88] = make_cmd(cmd_j6, 90, 4); // j6nz
  vm.memory[89] = make_cmd(cmd_nop);
  vm.memory[90] = make_cmd(cmd_ld6, 2000);
  vm.memory[91] = make_cmd(cmd_j6, 87, 3); // j6nn

  vm.memory[92] = make_cmd(cmd_hlt);

  vm.memory[150] = Word(POS_SIGN, 8, 0, 3, 5, 4);
  vm.memory[151] = Word(POS_SIGN, 0, 0, 0, 11, 11);
  vm.memory[152] = Word(POS_SIGN, 6, 7, 8, 9, 0);
  vm.memory[100] = Word(NEG_SIGN, 1, 2, 3, 4, 5);
  vm.memory[101] = Word(NEG_SIGN, 1, 2, 3, 4, 5);
  vm.memory[102] = Word(NEG_SIGN, 1, 2, 3, 4, 5);
  vm.memory[103] = Word(NEG_SIGN, 1, 2, 3, 4, 5);
  vm.memory[104] = Word(NEG_SIGN, 1, 2, 3, 4, 5);
  vm.memory[105] = Word(NEG_SIGN, 1, 2, 3, 4, 5);
  vm.memory[106] = Word(NEG_SIGN, 1, 1, 1, 1, 1);
  vm.memory[107] = Word(NEG_SIGN, 1, 1, 1, 1, 1);
  vm.memory[108] = Word(NEG_SIGN, 1, 1, 1, 1, 1);
  vm.memory[109] = Word(NEG_SIGN, 1, 1, 1, 1, 1);
  vm.memory[110] = Word(NEG_SIGN, 1, 1, 1, 1, 1);
  vm.memory[111] = Word(NEG_SIGN, 1, 1, 1, 1, 1);
  vm.memory[112] = Word(NEG_SIGN, 1, 1, 1, 1, 1);
  vm.memory[113] = Word(NEG_SIGN, 1, 1, 1, 1, 1);
  vm.memory[114] = Word(NEG_SIGN, 1, 1, 1, 1, 1);
  vm.memory[200] = Word(POS_SIGN, 1, 2, 3, 4, 5);
  vm.memory[210] = Word(POS_SIGN, 0, 0, 0, 0, 30);
  vm.memory[211] = Word(POS_SIGN, 0, 0, 0, 0, 50);
  vm.memory[220] = Word(POS_SIGN, 1, 1, 1, 1, 1);
  vm.memory[221] = Word(POS_SIGN, 1, 1, 1, 1, 1);
  vm.memory[230] = Word(POS_SIGN, 0, 1, 2, 3, 4);
  vm.memory[231] = Word(POS_SIGN, 5, 4, 3, 2, 1);
  vm.memory[232] = Word(POS_SIGN, 1, 1, 1, 1, 1);

  vm.print_state(ofs_start);

  vm.run(0);

  vm.memory[0] = make_cmd(cmd_ldan, 150);
  vm.memory[1] = make_cmd(cmd_ldxn, 150, encode_format(0, 3));
  vm.memory[2] = make_cmd(cmd_ld1n, 151);
  vm.memory[3] = make_cmd(cmd_ld2n, 151);
  vm.memory[4] = make_cmd(cmd_ld3n, 151);
  vm.memory[5] = make_cmd(cmd_ld4n, 151);
  vm.memory[6] = make_cmd(cmd_ld5n, 151);
  vm.memory[7] = make_cmd(cmd_ld6n, 151);
  vm.memory[8] = make_cmd(cmd_nop);
  vm.memory[9] = make_cmd(cmd_hlt);

  vm.print_state(ofs_result1);

  vm.run(0);

  vm.print_state(ofs_result2);
}

int main(int argc, char *const argv[]) {
  test_vm();
  return 0;
}
