#include "dataset.hpp"
#include <cassert>
#include <iostream>

class object {
public:
  int do_something() { return 1; }
};

int main() {
  int *a = new int{1};
  dataset<int> a_data;
  a_data.push_back(a);
  a_data[0] = 2;
  assert(*a == 2);

  dataset<object> data(1000);
  for (std::size_t i = 0; i < data.cap(); ++i) {
    data.push_back(new object());
  }
  int sum = 0;
  for (std::size_t i = 0; i < data.size(); ++i) {
    sum += data[i].do_something();
  }
  assert(sum == 1000);

  dataset<int> data2(100);
  for (int i = 0; i < data2.cap(); ++i) {
    data2.push_back(new int{i});
  }
  assert(data2.front() == 0 && data2.back() == data2.size() - 1);
  data2.push_back(new int{100});
  assert(data2.size() == 101);
  data2.pop_back();
  assert(data2.size() == 100);
  data2.erase(0, 50);
  assert(data2.size() == 50);
  delete data2.pull_out(49);
  assert(data2.size() == 49);

  return 0;
}
