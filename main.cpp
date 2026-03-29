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

bool testElementAccess()
{
  topit::Vector< int > v;
  v.push_back(1);
  try
  {
    int& val = v.at(0);
    return val == 1;
  }
  catch(...)
  {
    return false; 
  }
}

bool testElementOutOfBoundAccess()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementConstAccess()
{
  topit::Vector< int > v;
  v.push_back(1);
  const topit::Vector< int >& rv = v;
  try
  {
    const int& val = rv.at(0);
    return val == 1;
  }
  catch(...)
  {
    return false; 
  }
}

bool testElementOutOfBoundConstAccess()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range&)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testCopyConstructorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav{v};
  return v == yav;
}

bool testCopyConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.push_back(1);
  topit::Vector< int > yav = v;
  try
  {
    return yav.getSize() == v.getSize() && yav.at(0) == v.at(0);
  }
  catch(...)
  {
    return false;
  }
}

bool testMoveConstructor()
{
  topit::Vector< int > v{5, 2};
  topit::Vector< int > yav{std::move(v)};
  return yav.getSize() == 5 && v.isEmpty();
}

bool testCopyAssignment()
{
  topit::Vector< int > v{5, 2};
  topit::Vector< int > yav{2, 5};
  topit::Vector< int > temp{};

  temp = yav;
  yav = v;
  v = temp;

  bool test1 = v.getSize() == 2;
  bool test2 = yav.getSize() == 5;
  bool test3 = v.at(0) == 5;
  bool test4 = yav.at(0) == 2;
  return test1 && test2 && test3 && test4;
}

bool testSelfAssignment()
{
  topit::Vector< int > v{5, 2};
  v = v;
  return v.getSize() == 5 && v.at(0) == 2;
}

bool testMoveAssignment()
{
  topit::Vector< int > v{5, 2};
  topit::Vector< int > yav{4, 3};
  yav = std::move(v);
  return yav.getSize() == 5 && yav.at(0) == 2 && v.isEmpty();
}

bool testSelfMoveAssignment()
{
  topit::Vector< int > v{5, 2};
  v = std::move(v);
  return v.getSize() == 5 && v.at(0) == 2;
}

bool testInsert()
{
  auto vec = topit::Vector< int >();
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  vec.insert(1, 8);
  vec.insert(3, 7);
  vec.insert(5, 12);
  vec.insert(0, 23);
  int control[] = {23, 1, 8, 2, 7, 3, 12, 4, 5};
  bool res = vec.getSize() == 9;
  for (size_t i = 0; res && i < vec.getSize(); i++)
  {
    res = res && (vec[i] == control[i]);
  }
  return res;
}

bool testInsertByRange()
{
  topit::Vector< int > vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);

  topit::Vector< int > vec2;
  vec2.push_back(6);
  vec2.push_back(7);
  vec2.push_back(8);
  vec2.push_back(9);
  vec2.push_back(10);

  vec2.insert(2, vec, 1, 4);
  int control[] = {6, 7, 2, 3, 4, 8, 9, 10};
  
  bool res = vec2.getSize() == 8;
  for (size_t i = 0; res && i < vec2.getSize(); i++)
  {
    res = res && (vec2[i] == control[i]);
  }

  try
  {
    vec2.insert(7, vec, 0, 100);
    res = false;
  }
  catch (const std::out_of_range&)
  {}

  return res;
}

bool testErase()
{
  topit::Vector< int > v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.erase(2);
  int control[] = {1, 2, 4, 5};
  bool res = v.getSize() == 4;
  for (size_t i = 0; i < v.getSize(); ++i)
  {
    res = res && v[i] == control[i];
  }
  try
  {
    v.erase(100);
    return false;
  }
  catch (const std::out_of_range&)
  {}

  return res;
}

bool testEraseByRange()
{
  topit::Vector< int > v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);
  v.push_back(6);
  v.push_back(7);
  v.erase(2, 5);
  int control[] = {1, 2, 6, 7};
  bool res = v.getSize() == 4;
  for (size_t i = 0; i < v.getSize(); ++i)
  {
    res = res && v[i] == control[i];
  }
  try
  {
    v.erase(100, 3);
    return false;
  }
  catch (const std::out_of_range&)
  {}

  return res;
}

bool testInsertIteratorSingle()
{
  topit::Vector< int > v{5, 2};
  auto it = v.begin() + 2;

  auto ret = v.insert(it, 52);

  topit::Vector< int > yav{2, 2};
  yav.push_back(52);
  yav.push_back(2);
  yav.push_back(2);
  yav.push_back(2);

  bool res = (v == yav);
  res = res && (*ret == 52);

  return res;
}

bool testInsertIteratorBegin()
{
  topit::Vector< int > v{3, 2};
  v.insert(v.begin(), 1);

  topit::Vector< int > yav{3, 2};
  yav.insert(0, 1);
  
  return v == yav;
}

bool testInsertIteratorEnd()
{
  topit::Vector< int > v{3, 2};
  v.insert(v.end(), 99);

  topit::Vector< int > yav{3, 2};
  yav.push_back(99);
  
  return v == yav;
}

bool testInsertIteratorRange()
{
  topit::Vector< int > v{3, 1};

  topit::Vector< int > src{2, 5};

  v.insert(v.begin() + 1, src.begin(), src.end());

  topit::Vector< int > yav{3, 1};
  yav.insert(1, src, 0, src.getSize());

  return v == yav;
}

bool testInsertIteratorRangeEmpty()
{
  topit::Vector< int > v{3, 2};
  topit::Vector< int > src;
  
  v.insert(v.begin(), src.begin(), src.end());

  topit::Vector< int > yav{3, 2};

  return v == yav;
}

bool testInsertInitializerList()
{

  topit::Vector< int > v{3, 1};
  v.insert(v.begin() + 1, {10, 20, 30});

  topit::Vector< int > yav{3, 1};
  yav.insert(1, 10);
  yav.insert(2, 20);
  yav.insert(3, 30);
  
  return v == yav;
}

bool testInsertFromStdVector()
{
  topit::Vector< int > v{3, 1};
  std::vector< int > src{10, 20, 30};
  
  v.insert(v.begin() + 1, src.begin(), src.end());

  topit::Vector< int > yav{3, 1};
  yav.insert(1, 10);
  yav.insert(2, 20);
  yav.insert(3, 30);
  
  return v == yav;
}

bool testInsertFromArray()
{
  topit::Vector< int > v{3, 1};
  int arr[] = {10, 20, 30};
  
  v.insert(v.begin() + 1, arr, arr + 3);

  topit::Vector< int > yav{3, 1};
  yav.insert(1, 10);
  yav.insert(2, 20);
  yav.insert(3, 30);
  
  return v == yav;
}

bool testEraseIteratorSingle()
{
  topit::Vector< int > v{5, 2};
  v.erase(v.begin() + 2);

  topit::Vector< int > yav{4, 2};

  return v == yav;
}

bool testEraseIteratorBegin()
{
  topit::Vector< int > v{3, 5};
  v.erase(v.begin());

  topit::Vector< int > yav{2, 5};
  
  return v == yav;
}

bool testEraseIteratorEnd()
{
  topit::Vector< int > v{3, 5};
  v.erase(v.end() - 1);

  topit::Vector< int > yav{2, 5};
  
  return v == yav;
}

bool testEraseIteratorRange()
{
  topit::Vector< int > v{5, 2};
  v.erase(v.begin() + 1, v.begin() + 4);

  topit::Vector< int > yav{2, 2};
  
  return v == yav;
}

bool testEraseIteratorAll()
{
  topit::Vector< int > v{3, 5};
  v.erase(v.begin(), v.end());

  return v.isEmpty();
}

bool testEraseIteratorEmpty()
{
  topit::Vector< int > v{3, 5};
  v.erase(v.begin(), v.begin());

  topit::Vector< int > yav{3, 5};

  return v == yav;
}

bool testEraseIteratorReturn()
{
  topit::Vector< int > v{5, 2};
  auto ret = v.erase(v.begin() + 2);

  bool res = (*ret == 2);
  res = res && (ret - v.begin() == 2);

  return res;
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
    { "Multiple push back", testMultiplePushBack },
    { "Inbound access", testElementAccess },
    { "Out of bound access", testElementOutOfBoundAccess },
    { "Indound const access", testElementConstAccess},
    { "Out of bound const access", testElementOutOfBoundConstAccess },
    { "Copy empty vector", testCopyConstructorForEmpty },
    { "Copy non-empty vector", testCopyConstructorForNonEmpty },
    { "Copy move constructor", testMoveConstructor },
    { "Copy assignment", testCopyAssignment },
    { "Self assignment", testSelfAssignment },
    { "Move assignment", testMoveAssignment },
    { "Move self assignment", testSelfMoveAssignment },
    { "Insert", testInsert },
    { "Insert by range", testInsertByRange },
    { "Erase", testErase },
    { "Erase by range", testEraseByRange }
  };

  const size_t count = sizeof(tests) / sizeof(test_t);

  std::cout << std::boolalpha;
  size_t success = 0;
  size_t failed = 0;
  bool pass = true;

  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    success += res;
    failed += !res;
    std::cout << tests[i].first << ": " << res << '\n';
    pass = pass && res;
  }

  std::cout << "RESULT: " << pass << '\n';
  std::cout << "SUCCESS: " << success << '\n';
  std::cout << "FAILED: " << failed << '\n';
  return 0;
}
