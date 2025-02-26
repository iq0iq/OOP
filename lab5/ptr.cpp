#include <cassert>
#include <iostream>
#include <memory>

class parent {
public:
  parent() { std::cout << "parent_default_constructor\n"; }
  parent(const parent &other) { std::cout << "parent_copy_constructor\n"; }
  ~parent() { std::cout << "parent_destructor\n"; }
  int x = 0;
};

std::unique_ptr<parent> return_unique() {
  std::unique_ptr<parent> ptr2 = std::make_unique<parent>();
  return ptr2;
}

std::shared_ptr<parent> return_shared() {
  std::shared_ptr<parent> ptr2 = std::make_shared<parent>();
  return ptr2;
}

void test1() {
  parent *a = new parent;
  std::shared_ptr<parent> ptr2(a);
}

void test2() {
  parent *a = new parent;
  std::unique_ptr<parent> ptr(a);
}

void take_shared(std::shared_ptr<parent> ptr) { ptr->x = 1; }

void take_unique(std::unique_ptr<parent> &ptr) { ptr->x = 2; }

int main() {
  auto ptr1 = return_unique();
  std::cout << std::endl;
  test1();
  test2();
  std::cout << std::endl;
  std::shared_ptr<parent> ptr2 = return_shared();
  std::cout << std::endl;
  parent &x1 = *ptr1;
  parent &x2 = *ptr2;
  x1.x = 1;
  x2.x = 2;
  std::cout << ptr1->x << ' ' << ptr2->x << std::endl;
  std::cout << std::endl;
  std::shared_ptr<parent> ptr3(new parent);
  take_shared(ptr3);
  assert(ptr3->x == 1);
  std::unique_ptr<parent> ptr4(new parent);
  take_unique(ptr4);
  assert(ptr4->x == 2);
  std::cout << std::endl;
  return 0;
}