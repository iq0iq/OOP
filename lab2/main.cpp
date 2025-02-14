#include "quadrangle.hpp"
#include "triangle.hpp"
#include <iostream>

int main() {
  figure *something;
  segment seg{0, 0, 1, 1};
  something = &seg;
  std::cout << "centre of a segment (0, 0), (1, 1) : "
            << something->get_centre().first << ' '
            << something->get_centre().second << std::endl;

  point p0{0, 0};
  figure &some_figure = p0;
  std::cout << some_figure.get_centre().first << ' '
            << some_figure.get_centre().second << std::endl;

  quadrangle quad{{0, 0}, {1, 0}, {1, 1}, {0, 1}};

  convex_figure *manyangled = &quad;
  std::cout << "centre of a quadrangle (0, 0), (1, 0), (1, 1), (0, 1) : "
            << manyangled->get_centre().first << ' '
            << manyangled->get_centre().second << std::endl;
  std::cout << "perimeter: " << manyangled->get_perimeter() << std::endl;
  std::cout << "area: " << manyangled->get_area() << std::endl;

  triangle tree{point{0, 0}, point{1, 1}, point{0, 1}};
  manyangled = new triangle{{0, 0}, {1, 1}, {0, 1}};
  std::cout << "centre of a triangle (0, 0), (1, 1), (0, 1) : "
            << manyangled->get_centre().first << ' '
            << manyangled->get_centre().second << std::endl;
  std::cout << "perimeter: " << manyangled->get_perimeter() << std::endl;
  std::cout << "area: " << manyangled->get_area() << std::endl;
  delete manyangled;
  return 0;
}
