#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

// --- Day 4: Secure Container ---

// You arrive at the Venus fuel depot only to discover it's protected by a
// password. The Elves had written the password on a sticky note, but someone
// threw it out.

// However, they do remember a few key facts about the password:

//     It is a six-digit number.
//     The value is within the range given in your puzzle input.
//     Two adjacent digits are the same (like 22 in 122345).
//     Going from left to right, the digits never decrease; they only ever
//     increase or stay the same (like 111123 or 135679).

// Other than the range rule, the following are true:

//     111111 meets these criteria (double 11, never decreases).
//     223450 does not meet these criteria (decreasing pair of digits 50).
//     123789 does not meet these criteria (no double).

// How many different passwords within the range given in your puzzle input meet
// these criteria?

// Your puzzle input is 138307-654504.

bool all_ascending(const std::vector<int> &v) {
  assert(v.size() == 6);

  auto current = v.rbegin();
  auto next = current + 1;

  while (next != v.rend()) {
    if (*next < *current)
      return false;

    current++;
    next++;
  }

  return true;
}

bool unique_pair(const std::vector<int> &v) {
  auto current = v.begin();
  auto next = current + 1;
  while (next != v.end()) {
    auto nexter = next + 1;
    if (*current == *next && (nexter == v.end() || *nexter != *current) &&
        (current == v.begin() || *(current - 1) != *current))
      return true;
    current++;
    next++;
  }

  return false;
}

std::vector<int> n2v(int n) {
  std::vector<int> v;
  while (n != 0) {
    v.push_back(n % 10);
    n /= 10;
  }
  return v;
}

int solve1(int low, int high) {
  std::vector<int> n(high - low);
  std::iota(n.begin(), n.end(), low);

  int solutions = 0;

  for (auto &e : n) {
    auto v = n2v(e);

    if (all_ascending(v) && std::adjacent_find(v.begin(), v.end()) != v.end()) {
      solutions++;
    }
  }

  return solutions;
}

int solve2(int low, int high) {
  std::vector<int> n(high - low);
  std::iota(n.begin(), n.end(), low);

  int solutions = 0;

  for (auto &e : n) {
    auto v = n2v(e);

    if (all_ascending(v) && unique_pair(v)) {
      solutions++;
    }
  }

  return solutions;
}

int main(int argc, char **argv) {
  std::cout << solve1(138307, 654504) << std::endl;
  std::cout << solve2(138307, 654504) << std::endl;
}
