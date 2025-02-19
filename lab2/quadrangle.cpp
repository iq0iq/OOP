#include "quadrangle.hpp"

quadrangle::quadrangle(const point &a, const point &b, const point &c,
                       const point &d) {
  double a_angle = count_angle(d, a, b);
  double b_angle = count_angle(a, b, c);
  double c_angle = count_angle(b, c, d);
  double d_angle = count_angle(c, d, a);
  const double pi = acos(-1.0);
  if (a_angle < pi && b_angle < pi && c_angle < pi && d_angle < pi) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
  } else {
    throw std::invalid_argument("Not convex");
  }
}

quadrangle::quadrangle(const quadrangle &other)
    : a(other.a), b(other.b), c(other.c), d(other.d) {}

quadrangle::~quadrangle() {}

point quadrangle::get_a() const { return a; }

point quadrangle::get_b() const { return b; }

point quadrangle::get_c() const { return c; }

point quadrangle::get_d() const { return d; }

std::pair<double, double> quadrangle::get_centre() const {
  return std::make_pair((a.x + b.x + c.x + d.x) / 4,
                        (a.y + b.y + c.y + d.y) / 4);
}
double quadrangle::get_perimeter() const {
  segment ab{a, b};
  segment bc{b, c};
  segment cd{c, d};
  segment da{d, a};
  return ab.get_length() + bc.get_length() + cd.get_length() + da.get_length();
}

double quadrangle::get_area() const {
  return std::fabs(a.x * b.y + b.x * c.y + c.x * d.y + d.x * a.y - a.y * b.x -
                   b.y * c.x - c.y * d.x - d.y * a.x) /
         2;
}
