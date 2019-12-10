#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <optional>
#include <sstream>
#include <utility>
#include <vector>

using Step = std::pair<char, int>;

struct Point {
  int x;
  int y;
};

struct Line {
  Point p0;
  Point p1;
};

std::vector<Step> parse_string(const std::string &s) {
  std::vector<Step> walk;

  std::istringstream iss(s);
  char dir, delim;
  int dist;

  do {
    iss >> dir >> dist;
    walk.emplace_back(std::make_pair(dir, dist));
  } while (iss >> delim);

  return walk;
}

std::vector<Line> walk(const std::vector<Step> &w) {
  Point current_pos = {0, 0};
  std::vector<Line> path;

  for (auto &e : w) {
    Point new_pos = current_pos;

    switch (e.first) {
    case 'U':
      new_pos.y += e.second;
      break;
    case 'D':
      new_pos.y -= e.second;
      break;
    case 'R':
      new_pos.x += e.second;
      break;
    case 'L':
      new_pos.x -= e.second;
      break;
    default:
      throw std::exception();
    }

    path.push_back({current_pos, new_pos});
    current_pos = new_pos;
  }

  return path;
}

bool intersects(Line l1, Line l2) {

  if (l1.p0.x == l1.p1.x) {
    // Vertical
    if (l2.p0.x == l2.p1.x)
      return false;

    auto xmin = std::min(l2.p0.x, l2.p1.x);
    auto xmax = std::max(l2.p0.x, l2.p1.x);

    auto ymin = std::min(l1.p0.y, l1.p1.y);
    auto ymax = std::max(l1.p0.y, l1.p1.y);

    return (l2.p0.y < ymax && l2.p0.y > ymin && l1.p0.x < xmax &&
            l1.p0.x > xmin);

  } else {
    // Horizontal
    if (l2.p0.y == l2.p1.y)
      return false;

    auto xmin = std::min(l1.p0.x, l1.p1.x);
    auto xmax = std::max(l1.p0.x, l1.p1.x);

    auto ymin = std::min(l2.p0.y, l2.p1.y);
    auto ymax = std::max(l2.p0.y, l2.p1.y);

    return (l2.p0.x < xmax && l2.p0.x > xmin && l1.p0.y > ymin &&
            l1.p0.y < ymax);
  }
}

Point intersection(Line l1, Line l2) {
  if (l1.p0.x == l1.p1.x) {
    return {l1.p0.x, l2.p0.y};
  } else {
    return {l2.p0.x, l1.p0.y};
  }
}

int steps_to(const std::vector<Step> &steps, Point target) {
  Point current_pos = {0, 0};
  int steps_taken = 0;

  for (auto &e : steps) {
    Point new_pos = current_pos;

    switch (e.first) {
    case 'U':
      new_pos.y += e.second;
      break;
    case 'D':
      new_pos.y -= e.second;
      break;
    case 'R':
      new_pos.x += e.second;
      break;
    case 'L':
      new_pos.x -= e.second;
      break;
    default:
      throw std::exception();
    }

    auto xmin = std::min(new_pos.x, current_pos.x);
    auto xmax = std::max(new_pos.x, current_pos.x);
    auto ymin = std::min(new_pos.y, current_pos.y);
    auto ymax = std::max(new_pos.y, current_pos.y);

    if (xmin == xmax && target.x == xmin && target.y > ymin && target.y < ymax)
      return steps_taken + std::abs(target.y - current_pos.y);

    if (ymin == ymax && target.y == ymin && target.x > xmin && target.x < xmax)
      return steps_taken + std::abs(target.x - current_pos.x);

    current_pos = new_pos;
    steps_taken += e.second;
  }

  throw std::exception();
}

int main(int argc, char **argv) {
  std::ifstream ifs("input03");

  std::string first, second;
  ifs >> first >> second;

  std::vector<Step> first_walk = parse_string(first);
  std::vector<Step> second_walk = parse_string(second);

  // for (auto &e : first_walk)
  //   std::cout << e.first << e.second << std::endl;

  std::vector<Point> intersections;

  for (auto &l1 : walk(first_walk)) {
    for (auto &l2 : walk(second_walk)) {
      if (intersects(l1, l2)) {
        auto p = intersection(l1, l2);
        intersections.push_back(p);
      }
    }
  }

  std::cout << std::accumulate(intersections.begin(), intersections.end(),
                               std::numeric_limits<int>::max(),
                               [](auto v, auto p) {
                                 return std::min(v,
                                                 std::abs(p.x) + std::abs(p.y));
                               })
            << std::endl;

  int min_steps = std::numeric_limits<int>::max();

  std::cout << std::accumulate(intersections.begin(), intersections.end(),
                               std::numeric_limits<int>::max(),
                               [&](auto v, auto target) {
                                 return std::min(
                                     v, steps_to(first_walk, target) +
                                            steps_to(second_walk, target));
                               })
            << std::endl;
}
