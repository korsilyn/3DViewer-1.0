#ifndef C8_3DVIEWER_S21_TRANSFORM_H
#define C8_3DVIEWER_S21_TRANSFORM_H

#include "s21_3dviewer.h"
#include "s21_parse.h"

void move_x(obj_data *data, double distance);
void move_y(obj_data *data, double distance);
void move_z(obj_data *data, double distance);
void rotate_x(obj_data *data, double angle);
void rotate_y(obj_data *data, double angle);
void rotate_z(obj_data *data, double angle);
void scale(obj_data *data, double scale_param);

#endif  // C8_3DVIEWER_S21_TRANSFORM_H
