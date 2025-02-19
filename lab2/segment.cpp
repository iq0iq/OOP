#include "segment.hpp"

segment::segment(const point &first, const point &second) {
  if (first.x == second.x && first.y == second.y) {
    throw std::invalid_argument("Same point");
  }
  this->first = first;
  this->second = second;
}

segment::segment(const double x1, const double y1, const double x2,
                 const double y2) {
  if (x1 == x2 && y1 == y2)
    throw std::invalid_argument("Same point");
  first = point{x1, y1};
  second = point{x2, y2};
}

segment::segment(const segment &other)
    : first(other.first), second(other.second) {}

segment::~segment() {}

double segment::get_length() const {
  return std::sqrt((first.x - second.x) * (first.x - second.x) +
                   (first.y - second.y) * (first.y - second.y));
}

std::pair<double, double> segment::get_centre() const {
  return std::make_pair((first.x + second.x) / 2, (first.y + second.y) / 2);
}

point segment::p1() const { return first; }

point segment::p2() const { return second; }
