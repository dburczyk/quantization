#ifndef QUANTIZATION_VECTOR_H
#define QUANTIZATION_VECTOR_H

typedef struct Vector Vector;
struct Vector {
  void **data_;
  int size_;
};

#endif //QUANTIZATION_VECTOR_H
