#include "point.hpp"

class segment : public figure {
public:
  segment() = delete;
  segment(const point first, const point second);
  segment(const double x1, const double y1, const double x2, const double y2);
  segment(const segment &other);
  ~segment();

private:
  point first;
  point second;

public:
  double get_length() const;
  std::pair<double, double> get_centre() const;
  point p1() const;
  point p2() const;
};
