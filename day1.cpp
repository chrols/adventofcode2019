#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

int fuel_required(int mass) {
  if (mass <= 6) {
    return 0;
  } else {
    int fuel = mass / 3 - 2;
    return fuel + fuel_required(fuel);
  }
}

int main(int argc, char **argv) {
  std::ifstream ifs("input01");

  std::vector<int> mass;

  std::copy(std::istream_iterator<int>(ifs), std::istream_iterator<int>(),
            std::back_inserter(mass));

  int naive_fuel =
      std::accumulate(mass.begin(), mass.end(), 0,
                      [](auto x, auto y) { return x + y / 3 - 2; });

  std::cout << naive_fuel << std::endl;

  int fuel = std::accumulate(mass.begin(), mass.end(), 0, [](auto x, auto y) {
    return x + fuel_required(y);
  });

  std::cout << fuel << std::endl;
}
