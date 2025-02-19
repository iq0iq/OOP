#pragma once
#include "point.hpp"

class segment_pointed : public figure {
public:
  segment_pointed() = delete;
  segment_pointed(const point &first, const point &second);
  segment_pointed(const double x1, const double y1, const double x2,
                  const double y2);
  segment_pointed(const segment_pointed &other);
  ~segment_pointed();

private:
  point *first;
  point *second;

public:
  double get_length() const;
  std::pair<double, double> get_centre() const;
  point p1() const;
  point p2() const;
};
