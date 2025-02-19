#include "convex_figure.hpp"

class triangle : public convex_figure {
public:
  triangle() = delete;
  triangle(const point &a, const point &b, const point &c);
  triangle(const triangle &other);
  ~triangle();

private:
  point a;
  point b;
  point c;

public:
  point get_a() const;
  point get_b() const;
  point get_c() const;
  std::pair<double, double> get_centre() const;
  double get_perimeter() const;
  double get_area() const;
};
