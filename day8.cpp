#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

using Layer = std::vector<char>;
int layer_size = 25 * 6;

Layer merge_layers(Layer top, Layer bottom) {
  assert(top.size() == bottom.size());

  Layer m(layer_size);
  auto itt = top.begin();
  auto itb = bottom.begin();

  for (auto &e : m) {
    e = (*itt == '2') ? *itb : *itt;
    itt++;
    itb++;
  }

  return m;
}

int main(int argc, char **argv) {

  std::vector<Layer> layers;

  std::ifstream ifs("input08");
  char t;
  Layer l(layer_size);
  auto it = l.begin();

  while (ifs >> t) {
    *it = t;
    it++;
    if (it == l.end()) {
      layers.push_back(l);
      l = Layer(layer_size);
      it = l.begin();
    }
  }

  auto least_zeroes =
      std::min_element(layers.begin(), layers.end(), [](auto l1, auto l2) {
        return std::count(l1.begin(), l1.end(), '0') <
               std::count(l2.begin(), l2.end(), '0');
      });

  for (auto &e : *least_zeroes) {
    std::cout << e << " ";
  }

  std::cout << std::endl;

  auto num_ones = std::count(least_zeroes->begin(), least_zeroes->end(), '1');
  auto num_twos = std::count(least_zeroes->begin(), least_zeroes->end(), '2');
  std::cout << num_ones * num_twos << std::endl;

  auto composite = std::accumulate(layers.begin() + 1, layers.end(),
                                   *layers.begin(), merge_layers);

  for (int y = 0; y < 6; y++) {
    for (int x = 0; x < 25; x++) {
      std::cout << ((composite[y * 25 + x] == '1') ? 'H' : ' ');
    }
    std::cout << std::endl;
  }
}
