#pragma once
#include "segment.hpp"

class convex_figure : public figure {
public:
  convex_figure() = default;
  convex_figure(const convex_figure &other) = default;
  virtual ~convex_figure() = default;

  virtual double get_perimeter() const = 0;
  virtual double get_area() const = 0;

protected:
  double count_angle(const point &vertex, const point &left,
                     const point &right);
};
