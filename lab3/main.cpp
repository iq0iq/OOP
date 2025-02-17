#include "dataset.hpp"
#include <cassert>
#include <iostream>

class object {
public:
  int do_something() { return 1; }
};

int main() {

  dataset<object> data(1000);
  for (std::size_t i = 0; i < data.size(); ++i) {
    data[i] = object{};
  }
  int sum = 0;
  for (std::size_t i = 0; i < data.size(); ++i) {
    sum += data[i].do_something();
  }
  assert(sum == 1000);

  dataset<int> data2(100);
  for (std::size_t i = 0; i < data2.size(); ++i) {
    data2[i] = i;
  }
  assert(data2.front() == 0 && data2.back() == data2.size() - 1);
  data2.push_back(100);
  assert(data2.size() == 101);
  data2.pop_back();
  assert(data2.size() == 100);
  data2.erase(0, 50);
  assert(data2.size() == 50);

  return 0;
}
