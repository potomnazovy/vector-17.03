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

    void insert(size_t i, const Vector< T >& rhs, size_t start, size_t end);
    void erase(size_t start, size_t end);


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
void topit::Vector< T >::insert(size_t i, const T& v)
{
  if (i > size_)
  {
    throw std::out_of_range("Vector::insert: index out of range");
  }

  T* temp = static_cast< T* >(operator new(sizeof(T)));
  bool constructed = false;
  
  try
  {
    new (temp) T(v);
    constructed = true;

    if (size_ == cap_)
    {
      size_t new_cap = (cap_ == 0) ? 1 : cap_ * 2;
      grow(new_cap);
    }

    for (size_t j = size_; j > i; --j)
    {
      new (&data_[j]) T(std::move(data_[j-1]));
      data_[j-1].~T();
    }

    new (&data_[i]) T(std::move(*temp));
    temp->~T();
    operator delete(temp);
    
    ++size_;
    
  }
  catch (...)
  {
    if (constructed)
    {
      temp->~T();
    }
    operator delete(temp);
    throw;
  }
}

template< class T >
void topit::Vector< T >::insert(size_t i, const Vector< T >& rhs, size_t start, size_t end)
{
  if (i > size_ || start > end || end > rhs.size_)
  {
    throw std::out_of_range("Vector::insert: invalid range");
  }
  
  size_t count = end - start;
  if (count == 0)
  {
    return;
  }

  if (size_ + count > cap_)
  {
    size_t new_cap = (cap_ == 0) ? count : std::max(cap_ * 2, size_ + count);
    grow(new_cap);
  }

  size_t total = count + (size_ - i);
  T* buffer = static_cast< T* >(operator new(sizeof(T) * total));
  size_t constructed = 0;
  
  try
  {
    for (size_t j = 0; j < count; ++j)
    {
      new (&buffer[j]) T(rhs.data_[start + j]);
      ++constructed;
    }

    for (size_t j = 0; j < size_ - i; ++j)
    {
      new (&buffer[count + j]) T(data_[i + j]);
      ++constructed;
    }

    for (size_t j = i; j < size_; ++j)
    {
      data_[j].~T();
    }

    for (size_t j = 0; j < total; ++j)
    {
      new (&data_[i + j]) T(buffer[j]);
      buffer[j].~T();
    }
    
    operator delete(buffer);
    size_ += count;
  }
  catch (...)
  {
    for (size_t j = 0; j < constructed; ++j)
    {
      buffer[j].~T();
    }
    operator delete(buffer);
    throw;
  }
}

template< class T >
void topit::Vector< T >::erase(size_t i)
{
  if (i >= size_)
  {
    throw std::out_of_range("Vector::erase: index out of range");
  }
  
  size_t count = size_ - i - 1;

  if (count == 0)
  {
    data_[i].~T();
    --size_;
    return;
  }

  T* temp = static_cast< T* >(operator new(sizeof(T) * count));
  size_t constructed = 0;
  
  try
  {
    for (size_t j = 0; j < count; ++j)
    {
      new (&temp[j]) T(data_[i + 1 + j]);
      ++constructed;
    }

    data_[i].~T();

    for (size_t j = 0; j < count; ++j)
    {
      new (&data_[i + j]) T(temp[j]);
      temp[j].~T();
      data_[i + 1 + j].~T();
    }
    
    operator delete(temp);
    --size_;
  }
  catch (...)
  {
    for (size_t j = 0; j < constructed; ++j)
    {
      temp[j].~T();
    }
    operator delete(temp);
    throw;
  }
}

template< class T >
void topit::Vector< T >::erase(size_t start, size_t end)
{
  if (start > end || end > size_)
  {
    throw std::out_of_range("Vector::erase: invalid range");
  }
  
  size_t count = end - start;
  if (count == 0)
  {
    return;
  }

  if (end == size_)
  {
    for (size_t j = start; j < end; ++j)
    {
      data_[j].~T();
    }
    size_ = start;
    return;
  }

  size_t save_count = size_ - end;
  T* buffer = static_cast< T* >(operator new(sizeof(T) * save_count));
  size_t constructed = 0;
  
  try
  {
    for (size_t j = 0; j < save_count; ++j)
    {
      new (&buffer[j]) T(data_[end + j]);
      ++constructed;
    }

    for (size_t j = start; j < size_; ++j)
    {
      data_[j].~T();
    }

    for (size_t j = 0; j < save_count; ++j)
    {
      new (&data_[start + j]) T(buffer[j]);
      buffer[j].~T();
    }
    
    operator delete(buffer);
    size_ -= count;
  }
  catch (...)
  {
    for (size_t j = 0; j < constructed; ++j)
    {
      buffer[j].~T();
    }
    operator delete(buffer);
    throw;
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
