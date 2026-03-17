#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>
namespace topit
{
  template< class T >
  struct Vector
  {
    Vector();
    ~Vector();

    Vector(const Vector&);
    Vector(Vector&&);
    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&);

    bool isEmpty() const noexcept; // чуть-чуть поменять
    size_t getSize() const noexcept; // доделать
    size_t getCapacity() const noexcept; // доделать

    void push_back(const T& value); // доделать
    void popBack(); // доделать
    void insert(size_t i, const T& v);
    void erase(size_t i);

  private:
    T* data_;
    size_t size_, cap_;
  };
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  cap_(0)
{

}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
void topit::Vector< T >::push_back(const T& value)
{

}

#endif
