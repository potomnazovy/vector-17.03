#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP
#include <cstddef>
#include <utility>
#include <stdexcept>
#include <new>
#include <algorithm>

// Классная
// Тестирование для копирования и перемещения
// Написать по 2 штуки insert, erase и протестировать (ДЛЯ ДИАПАЗОНА ЗНАЧЕНИЙ) строгая гарантия

// Домашка
// Итераторы для вектора (произвольного доступа)
// Придумать несколько insert/erase с итераторами (по 3 штуки) + тесты

namespace topit
{
  template< class T >
  struct Vector
  {
    Vector();
    ~Vector();
    Vector(size_t size, const T& init);

    Vector(const Vector< T >&);
    Vector(Vector< T >&&) noexcept;
    Vector< T >& operator=(const Vector< T >&);
    Vector< T >& operator=(Vector< T >&&) noexcept;

    void swap(Vector< T >& rhs) noexcept;

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

    void insert(size_t i, const Vector< T >& rhs, size_t start, size_t end); // классная
    void erase(size_t start, size_t end); // классная


    template< class FwdIterator > // домашка
    void insert(VectorIterator pos, FwdIterator begin, FwdIterator end);

  private:
    T* data_;
    size_t size_, cap_;

    explicit Vector(size_t size);
    void destroyAll() noexcept;
    void grow(size_t new_cap);
  };
  template< class T >
  bool operator==(const Vector< T >& lhs, const Vector< T >& rhs);
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  cap_(0)
{}

template< class T >
topit::Vector< T >::~Vector()
{
  destroyAll();
  operator delete(data_);
}

template< class T >
void topit::Vector< T >::destroyAll() noexcept
{
  for (size_t i = 0; i < size_; ++i)
  {
    data_[i].~T();
  }
  size_ = 0;
}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? static_cast< T* >(operator new(sizeof(T) * size)) : nullptr),
  size_(0),
  cap_(size)
{}

template< class T >
topit::Vector< T >::Vector(size_t size, const T& init):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    new (&data_[i]) T(init);
  }
  size_ = size;
}

template< class T >
topit::Vector< T >::Vector(const Vector< T > & rhs):
  Vector(rhs.getCapacity())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    new (&data_[i]) T(rhs.data_[i]);
  }
  size_ = rhs.size_;
}

template< class T >
topit::Vector< T >::Vector(Vector< T >&& rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  cap_(rhs.cap_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
  rhs.cap_ = 0;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(const Vector< T >& rhs)
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy = rhs;
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T >& topit::Vector< T >::operator=(Vector< T >&& rhs) noexcept
{
  if (this == std::addressof(rhs))
  {
    return *this;
  }
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
}

template< class T >
void topit::Vector< T >::swap(Vector< T >& rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(cap_, rhs.cap_);
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
  return const_cast< T& >(cthis->at(id));
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

template < class T >
void topit::Vector< T >::grow(size_t new_cap)
{
  T* new_data = static_cast< T* >(operator new(sizeof(T) * new_cap));

  for (size_t i = 0; i < size_; ++i)
  {
    new (&new_data[i]) T(std::move(data_[i]));
    data_[i].~T();
  }
  operator delete(data_);
  data_ = new_data;
  cap_ = new_cap;
}

template< class T >
void topit::Vector< T >::push_back(const T& value)
{
  if (size_ == cap_)
  {
    size_t new_cap = (cap_ == 0) ? 1 : cap_ * 2;
    grow(new_cap);
  }

  new (&data_[size_]) T(value);
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

template< class T >
bool topit::operator==(const Vector< T >& lhs, const Vector< T >& rhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
  return isEqual;
}

#endif
