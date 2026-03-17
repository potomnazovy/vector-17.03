#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>

template< class T >
struct Vector
{
  T* data;
  size_t size, cap;
};


#endif