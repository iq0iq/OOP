#include <cassert>
#include <iostream>
#include <string>

class parent {
public:
  parent() { std::cout << "parent_default_constructor\n"; }
  parent(const parent &other) { std::cout << "parent_copy_constructor\n"; }
  parent(parent *other) { std::cout << "parent_pointer_constructor\n"; }
  virtual ~parent() { std::cout << "parent_destructor\n"; }

  virtual std::string classname() { return "parent"; }
  virtual bool is_a(std::string classname) { return classname == "parent"; }
  virtual void work() { std::cout << "parent_works\n"; }
  void rest() { std::cout << "parent_rests\n"; }
  void method1() {
    std::cout << "method1\n";
    rest();
  }
  void method2() {
    std::cout << "method2\n";
    work();
  }
};

class child1 : public parent {
public:
  child1() { std::cout << "child1_default_constructor\n"; }
  child1(const child1 &other) { std::cout << "child1_copy_constructor\n"; }
  child1(child1 *other) { std::cout << "child1_pointer_constructor\n"; }
  ~child1() { std::cout << "child1_destructor\n"; }

  std::string classname() { return "child1"; }
  bool is_a(std::string classname) {
    return classname == "child1" || classname == "parent";
  }
  void work() { std::cout << "child1_works\n"; }
  void rest() { std::cout << "child1_rests\n"; }
};

class child2 : public parent {
public:
  child2() { std::cout << "child2_default_constructor\n"; }
  child2(const child2 &other) { std::cout << "child2_copy_constructor\n"; }
  child2(child2 *other) { std::cout << "child2_pointer_constructor\n"; }
  ~child2() { std::cout << "child2_destructor\n"; }

  std::string classname() { return "child2"; }
  bool is_a(std::string classname) {
    return classname == "child2" || classname == "parent";
  }
};

int main() {
  parent p1;
  child1 c1;
  child2 c2;
  c1.work();
  c1.parent::work();
  c2.work();
  std::cout << "\n";

  parent *pp = new parent;
  child1 *cc = new child1;
  pp->rest();
  cc->rest();
  pp->work();
  cc->work();
  delete pp;
  delete cc;
  std::cout << "\n";

  c1.method1();
  c1.method2();
  std::cout << "\n";

  p1 = c1;
  std::cout << p1.classname() << '\n';
  assert(p1.is_a("parent"));
  p1 = c2;
  std::cout << p1.classname() << '\n';
  parent *p2;
  p2 = &c1;
  std::cout << p2->classname() << '\n';
  assert(p2->is_a("child1") && p2->is_a("parent"));
  p2 = &c2;
  std::cout << p2->classname() << '\n';
  assert(p2->is_a("child2") && p2->is_a("parent"));

  child2 *c3 = dynamic_cast<child2 *>(p2);
  std::cout << c3->classname() << '\n';
  assert(c3->is_a("child2"));

  child1 *c4 = dynamic_cast<child1 *>(p2); // from child2 to child1
  // std::cout << c4->classname() << '\n'; segmentation fault

  parent *p3 = new child1;
  delete p3; // need a virtual destructor
  return 0;
}
