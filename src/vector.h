#ifndef VECTOR_H_
#define VECTOR_H_

#include <string.h>

typedef struct Vector Vector;
struct Vector {

  void **data_;

  size_t capacity_;

  size_t size_;
};

Vector *NewVector();

#endif //VECTOR_H_
