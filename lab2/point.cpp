#include "point.hpp"

point::point() : x(0), y(0) {}

point::point(const double x, const double y) : x(x), y(y) {}

point::point(const point &other) : x(other.x), y(other.y) {}

point::~point() {}

std::pair<double, double> point::get_centre() const {
  return std::make_pair(x, y);
}
