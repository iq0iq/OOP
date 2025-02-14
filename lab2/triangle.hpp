#include "convex_figure.hpp"

class triangle : public convex_figure {
public:
  triangle() = delete;
  triangle(point a, point b, point c);
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
