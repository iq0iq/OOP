#pragma once
#include <cmath>
#include <stdexcept>

class figure {
public:
  figure() = default;
  figure(const figure &other) = default;
  virtual ~figure() = default;

  virtual std::pair<double, double> get_centre() const = 0;
};
