#include <iostream>
#include <iomanip>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testNotEmptyVector()
{
  topit::Vector< int > v;
  v.push_back(10);
  return !v.isEmpty();
}

bool testPushBackAndSize()
{
  topit::Vector< int > v;
  v.push_back(10);
  bool test1 = v.getSize() == 1;
  v.push_back(20);
  bool test2 = v.getSize() == 2;
  v.push_back(30);
  bool test3 = v.getSize() == 3;
  return test1 && test2 && test3;
}

bool testGetSizeAfterPop()
{
  topit::Vector< int > v;
  v.push_back(10);
  v.push_back(20);
  v.push_back(30);
  v.popBack();
  return v.getSize() == 2;
}

bool testGetCapacity()
{
  topit::Vector< int > v;
  v.push_back(10);
  bool test1 = v.getCapacity() == 1;
  v.push_back(20);
  bool test2 = v.getCapacity() == 2;
  v.push_back(30);
  bool test3 = v.getCapacity() == 4;
  v.push_back(40);
  bool test4 = v.getCapacity() == 4;
  return test1 && test2 && test3 && test4;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.push_back(52);
  v.push_back(67);
  v.popBack();
  bool test1 = v.getSize() == 1;
  v.popBack();
  bool test2 = v.getSize() == 0;
  return test1 && test2;
}

bool testPopBackOnEmpty()
{
  topit::Vector< int > v;
  v.popBack();
  return v.getSize() == 0;
}

bool testMultiplePushBack()
{
  topit::Vector< int > v;
  for (int i = 0; i < 100; ++i)
  {
    v.push_back(i);
  }
  return v.getSize() == 100;
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] =
  {
    { "Empty vector", testEmptyVector },
    { "Not empty vector", testNotEmptyVector },
    { "Push back and size", testPushBackAndSize },
    { "Size after pop", testGetSizeAfterPop },
    { "Capacity growth", testGetCapacity },
    { "Pop back", testPopBack },
    { "Pop back on empty", testPopBackOnEmpty },
    { "Multiple push back", testMultiplePushBack }
  };

  const size_t count = sizeof(tests) / sizeof(test_t);

  std::cout << std::boolalpha;
  bool pass = true;

  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << '\n';
    pass = pass && res;
  }

  std::cout << "RESULT: " << pass << '\n';
  return 0;
}
