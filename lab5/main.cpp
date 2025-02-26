#include <iostream>
#include <vector>

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

parent func1() {
  parent x;
  return x;
}
parent *func2() {
  parent x;
  return &x;
}
parent &func3() {
  parent x;
  return x;
}
parent func4() {
  parent *x = new parent;
  return *x;
}
parent *func5() {
  parent *x = new parent;
  return x;
}
parent &func6() {
  parent *x = new parent;
  return *x;
}

int main() {
  parent p1;
  child c1;
  std::cout << "func1(parent obj)\n";
  func1(p1);
  std::cout << "func2(parent *obj)\n";
  func2(&p1);
  std::cout << "func3(parent &obj)\n";
  func3(p1);
  std::cout << "func1(parent obj)\n";
  func1(c1);
  std::cout << "func2(parent *obj)\n";
  func2(&c1);
  std::cout << "func3(parent &obj)\n";
  func3(c1);
  std::cout << std::endl;

  std::cout << "func 1,2,3,4,5,6\n";
  std::cout << "1: ";
  auto x1 = func1();
  std::cout << "2: ";
  auto x2 = func2();
  std::cout << "3: ";
  auto &x3 = func3();
  std::cout << "4: ";
  auto x4 = func4(); // not deleted
  std::cout << "5: ";
  auto x5 = func5();
  delete x5;
  std::cout << "6: ";
  parent &x6 = func6();
  delete &x6;
  std::cout << std::endl;
  return 0;
}
