#include <iostream>

class parent {
public:
  parent() { std::cout << "parent_default_constructor\n"; }
  parent(const parent &other) { std::cout << "parent_copy_constructor\n"; }
  parent(parent *other) { std::cout << "parent_pointer_constructor\n"; }
  ~parent() { std::cout << "parent_destructor\n"; }
};

class child : public parent {
public:
  child() { std::cout << "child_default_constructor\n"; }
  child(const child &other) { std::cout << "child_copy_constructor\n"; }
  child(child *other) { std::cout << "child_pointer_constructor\n"; }
  ~child() { std::cout << "child_destructor\n"; }
};

void func1(parent obj) {}
void func2(parent *obj) {}
void func3(parent &obj) {}

parent func1() {}
parent *func2() {}
parent &func3() {}
parent func4() {}
parent *func5() {}
parent &func6() {}

int main() {
  parent p1;
  child c1;
  std::cout << "func1\n";
  func1(p1);
  std::cout << "func2\n";
  func2(&p1);
  std::cout << "func3\n";
  func3(p1);
  std::cout << "func1\n";
  func1(c1);
  std::cout << "func2\n";
  func2(&c1);
  std::cout << "func3\n";
  func3(c1);
  return 0;
}
