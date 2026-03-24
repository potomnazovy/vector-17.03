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

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T& operator[](size_t id) noexcept;
    const T& operator[](size_t id) const noexcept;
    T& at(size_t id);
    const T& at(size_t id) const;

    void push_back(const T& value);
    void popBack();
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
T& topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T >* cthis = this;
  return const_cast< T& >((*cthis)[id]);
}

template< class T >
const T& topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
T& topit::Vector< T >::at(size_t id)
{
  const Vector< T >* cthis = this;
  return const_cast< T& >(cthis->at(pos));
}


template< class T >
const T& topit::Vector< T >::at(size_t id) const
{
  if (id < getSize())
  {
    return (*this).operator[](id);
  }
  throw std::out_of_range("bad id");
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
