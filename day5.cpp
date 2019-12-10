#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

enum Ins {
  ADD = 1,
  MUL = 2,
  INPUT = 3,
  OUTPUT = 4,
  JMPT = 5,
  JMPZ = 6,
  LT = 7,
  EQ = 8,
};

void evaluate_program(std::vector<int> code, int input) {
  int pc = 0;

  while (code[pc] != 99) {

    int op = code[pc] % 100;

    int mode = code[pc] / 100;
    bool x_immediate = (mode % 10 == 1);
    bool y_immediate = (mode / 10 == 1);
    bool dest_immediate = (mode / 100 == 1);

    if (dest_immediate) {
      std::cerr << "Dest immediate?" << std::endl;
      return;
    }

    int x = x_immediate ? code[pc + 1] : code[code[pc + 1]];
    int y = y_immediate ? code[pc + 2] : code[code[pc + 2]];
    int dest = code[pc + 3];

    switch (op) {
    case Ins::ADD:
      code[dest] = x + y;
      pc += 4;
      break;
    case Ins::MUL:
      code[dest] = x * y;
      pc += 4;
      break;
    case Ins::INPUT:
      code[code[pc + 1]] = input;
      pc += 2;
      break;
    case Ins::OUTPUT:
      std::cout << x << std::endl;
      pc += 2;
      break;
    case Ins::JMPT:
      if (x != 0) {
        pc = y;
      } else {
        pc += 3;
      }
      break;
    case Ins::JMPZ:
      if (x == 0) {
        pc = y;
      } else {
        pc += 3;
      }
      break;
    case Ins::LT:
      code[dest] = (x < y) ? 1 : 0;
      pc += 4;
      break;
    case Ins::EQ:
      code[dest] = (x == y) ? 1 : 0;
      pc += 4;
      break;
    default:
      std::cerr << "Error! Op:" << op << std::endl;
      return;
    }
  }

  return;
}

int main(int argc, char **argv) {
  std::ifstream ifs("input05");

  std::vector<int> code;

  int n;
  char delim;

  do {
    ifs >> n;
    code.push_back(n);
  } while (ifs >> delim);

  evaluate_program(code, 1);
  evaluate_program(code, 5);
}
