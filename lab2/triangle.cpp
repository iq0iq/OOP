#include "triangle.hpp"

triangle::triangle(const point &a, const point &b, const point &c) {
  double ab = (segment{a, b}).get_length();
  double bc = (segment{b, c}).get_length();
  double ac = (segment{a, c}).get_length();
  if (ab < bc + ac && bc < ab + ac && ac < ab + bc) {
    this->a = a;
    this->b = b;
    this->c = c;
  } else {
    throw std::invalid_argument("Not a triangle");
  }
}

triangle::triangle(const triangle &other)
    : a(other.a), b(other.b), c(other.c) {}

triangle::~triangle() {}

point triangle::get_a() const { return a; }

point triangle::get_b() const { return b; }

point triangle::get_c() const { return c; }

std::pair<double, double> triangle::get_centre() const {
  return std::make_pair((a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3);
}
double triangle::get_perimeter() const {
  double ab = (segment{a, b}).get_length();
  double bc = (segment{b, c}).get_length();
  double ac = (segment{a, c}).get_length();
  return ab + bc + ac;
}

double triangle::get_area() const {
  return std::fabs(a.x * b.y + b.x * c.y + c.x * a.y - a.y * b.x - b.y * c.x -
                   c.y * a.x) /
         2;
}
