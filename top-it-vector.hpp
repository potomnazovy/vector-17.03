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
  return size_ == 0;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return cap_;
}

template< class T >
void topit::Vector< T >::push_back(const T& value)
{
  if (size_ == cap_)
  {
    size_t new_cap = (cap_ == 0) ? 1 : cap_ * 2;

    T* new_data = new T[new_cap];

    for (size_t i = 0; i < size_; ++i)
    {
      new_data[i] = data_[i];
    }

    delete[] data_;

    data_ = new_data;
    cap_ = new_cap;
  }

  data_[size_] = value;
  ++size_;
}

template< class T >
void topit::Vector< T >::popBack()
{
  if (size_ > 0)
  {
    --size_;
    data_[size_].~T();
  }
}

#endif
