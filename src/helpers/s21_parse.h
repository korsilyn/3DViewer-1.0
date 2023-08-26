#ifndef C8_3DVIEWER_S21_PARSE_H
#define C8_3DVIEWER_S21_PARSE_H

#include "s21_3dviewer.h"

int s21_malloc_data(obj_data *data);
void s21_dealloc_data(obj_data *data);
int s21_read_obj_file(obj_data *data, const char *file);
void s21_data_count(obj_data *data, FILE *fp);
int s21_data_parse(obj_data *data, FILE *fp);

#endif  // C8_3DVIEWER_S21_PARSE_H
