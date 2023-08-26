#ifndef C8_3DVIEWER_S21_3DVIEWER_H
#define C8_3DVIEWER_S21_3DVIEWER_H

#define OK 1
#define ERROR 0

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data {
  size_t vertex_count;
  float *vertex_array;
  size_t vertex_indices_count;
  int *vertex_indices_array;
} obj_data;

#endif  // C8_3DVIEWER_S21_3DVIEWER_H
