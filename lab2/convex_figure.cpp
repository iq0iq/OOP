#include "convex_figure.hpp"

double convex_figure::count_angle(point vertex, point left, point right) {
  double v1 = vertex.x - left.x;
  double v2 = vertex.y - left.y;
  double v3 = right.x - left.x;
  double v4 = right.y - left.y;
  return std::acos((v1 * v3 + v2 * v4) /
                   (sqrt(v1 * v1 + v2 * v2) * sqrt(v3 * v3 + v4 * v4)));
}
