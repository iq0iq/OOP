#include "convex_figure.hpp"

class quadrangle : public convex_figure {
public:
  quadrangle() = delete;
  quadrangle(const point &a, const point &b, const point &c, const point &d);
  quadrangle(const quadrangle &other);
  ~quadrangle();

private:
  point a;
  point b;
  point c;
  point d;

public:
  point get_a() const;
  point get_b() const;
  point get_c() const;
  point get_d() const;
  std::pair<double, double> get_centre() const;
  double get_perimeter() const;
  double get_area() const;
};