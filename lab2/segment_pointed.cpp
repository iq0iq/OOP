#include "segment_pointed.hpp"

segment_pointed::segment_pointed(const point &first, const point &second) {
  if (first.x == second.x && first.y == second.y) {
    throw std::invalid_argument("Same point");
  }
  this->first = new point{first};
  this->second = new point{second};
}

segment_pointed::segment_pointed(double x1, double y1, double x2, double y2) {
  if (x1 == x2 && y1 == y2)
    throw std::invalid_argument("Same point");
  first = new point{x1, y1};
  second = new point{x2, y2};
}

segment_pointed::segment_pointed(const segment_pointed &other)
    : first(other.first), second(other.second) {
  first = new point{*other.first};
  second = new point{*other.second};
}

segment_pointed::~segment_pointed() {
  delete first;
  delete second;
}

double segment_pointed::get_length() const {
  return std::sqrt((first->x - second->x) * (first->x - second->x) +
                   (first->y - second->y) * (first->y - second->y));
}

std::pair<double, double> segment_pointed::get_centre() const {
  return std::make_pair((first->x + second->x) / 2, (first->y + second->y) / 2);
}

point segment_pointed::p1() const { return *first; }

point segment_pointed::p2() const { return *second; }
