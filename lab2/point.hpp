#include "figure.hpp"

class point : public figure {
public:
  point();
  point(const double x, const double y);
  point(const point &other);
  ~point();

public:
  double x;
  double y;

  std::pair<double, double> get_centre() const;
};
