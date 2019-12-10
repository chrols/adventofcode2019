#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int evaluate_program(std::vector<int> code, int noun, int verb) {
  int pc = 0;

  code[1] = noun;
  code[2] = verb;

  while (code[pc] != 99) {
    int x = code[pc + 1];
    int y = code[pc + 2];
    int dest = code[pc + 3];

    if (code[pc] == 1) {
      code[dest] = code[x] + code[y];
    } else if (code[pc] == 2) {
      code[dest] = code[x] * code[y];
    } else {
      std::cerr << "Error!" << std::endl;
      return -1;
    }

    pc += 4;
  }

  return code[0];
}

int main(int argc, char **argv) {
  std::ifstream ifs("input02");

  std::vector<int> code;

  int n;
  char delim;

  do {
    ifs >> n;
    code.push_back(n);
  } while (ifs >> delim);

  std::cout << evaluate_program(code, 12, 2) << std::endl;

  int target = 19690720;

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      if (evaluate_program(code, i, j) == target) {
        std::cout << i * 100 + j << std::endl;
        return 0;
      }
    }
  }
}
