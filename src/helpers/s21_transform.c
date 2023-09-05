#include "s21_transform.h"

// i is x, i + 1 is y, i + 2 is z in vertex_array

void move_x(obj_data *data, double distance) {
  for (size_t i = 0; i < data->vertex_count * 4; i += 4)
    data->vertex_array[i] += distance;
}

void move_y(obj_data *data, double distance) {
  for (size_t i = 0; i < data->vertex_count * 4; i += 3) {
    i += 1;
    data->vertex_array[i] += distance;
  }
}

void move_z(obj_data *data, double distance) {
  for (size_t i = 0; i < data->vertex_count * 4; i += 2) {
    i += 2;
    data->vertex_array[i] += distance;
  }
}

void rotate_x(obj_data *data, double angle) {
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < data->vertex_count * 4; i += 4) {
    double y = data->vertex_array[i + 1], z = data->vertex_array[i + 2];
    data->vertex_array[i + 1] = y * cos(angle) + z * sin(angle);
    data->vertex_array[i + 2] = -y * sin(angle) + z * cos(angle);
  }
}

void rotate_y(obj_data *data, double angle) {
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < data->vertex_count * 4; i += 4) {
    double x = data->vertex_array[i], z = data->vertex_array[i + 2];
    data->vertex_array[i] = x * cos(angle) + z * sin(angle);
    data->vertex_array[i + 2] = -x * sin(angle) + z * cos(angle);
  }
}

void rotate_z(obj_data *data, double angle) {
  angle = angle * M_PI / 180;
  for (size_t i = 0; i < data->vertex_count * 4; i += 4) {
    double x = data->vertex_array[i], y = data->vertex_array[i + 1];
    data->vertex_array[i] = x * cos(angle) + y * sin(angle);
    data->vertex_array[i + 1] = -x * sin(angle) + y * cos(angle);
  }
}

void scale(obj_data *data, double scale_param) {
  if (scale_param)
    for (size_t i = 0; i < data->vertex_count * 4; i++)
      data->vertex_array[i] *= scale_param;
}
