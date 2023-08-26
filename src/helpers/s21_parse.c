#include "s21_parse.h"

int s21_malloc_data(obj_data *data) {
  int status = OK;

  if (data->vertex_count)
    data->vertex_array =
        calloc(data->vertex_count * 4, sizeof(float));  // * 4 bc xyzw dots

  if (data->vertex_indices_count)
    data->vertex_indices_array =
        calloc(data->vertex_indices_count * 2,
               sizeof(int));  // * 2 bc face have 2 coords

  if (!data->vertex_array || !data->vertex_indices_array) status = ERROR;

  return status;
}

void s21_dealloc_data(obj_data *data) {
  if (data && data->vertex_array) {
    free(data->vertex_array);
    data->vertex_count = 0;
  }
  if (data && data->vertex_indices_array) {
    free(data->vertex_indices_array);
    data->vertex_indices_count = 0;
  }
}

int s21_read_obj_file(obj_data *data, const char *file) {
  if (!data || !file) return ERROR;
  int status = OK;
  FILE *fp = fopen(file, "r");
  if (fp) {
    s21_data_count(data, fp);
    status = s21_malloc_data(data);
    if (status == OK) {
      fseek(fp, 0, SEEK_SET);
      status = s21_data_parse(data, fp);
    }
    fclose(fp);
  } else
    status = ERROR;
  return status;
}

void s21_data_count(obj_data *data, FILE *fp) {
  char *line = NULL;
  size_t len = 0;

  while (getline(&line, &len, fp) != EOF) {
    if (strncmp(line, "v ", 2) == 0)
      data->vertex_count++;
    else if (strncmp(line, "f ", 2) == 0)
      for (char *vertex_index = strtok(line + 2, " "); vertex_index;
           vertex_index = strtok(NULL, " "))
        if (atoi(vertex_index)) data->vertex_indices_count++;
  }

  if (line) free(line);
}

int s21_data_parse(obj_data *data, FILE *fp) {
  int status = OK;
  char *line = NULL;
  size_t len = 0;
  size_t index = 0;
  size_t vertex_count = 0;
  size_t vertex_indices_count = 0;

  while (getline(&line, &len, fp) != EOF) {
    if (strncmp(line, "v ", 2) == 0) {
      vertex_count++;
      double x, y, z, w;
      int cnt = sscanf(line, "v %lf %lf %lf %lf", &x, &y, &z, &w);
      data->vertex_array[index++] = x;
      data->vertex_array[index++] = y;
      data->vertex_array[index++] = z;
      if (cnt == 4)
        data->vertex_array[index++] = w;
      else
        data->vertex_array[index++] = 1.0;
    } else if (strncmp(line, "f ", 2) == 0) {
      int first_index = 0;
      int is_first_index = 0;
      for (char *vertex_index = strtok(line + 2, " "); vertex_index;
           vertex_index = strtok(NULL, " ")) {
        int index_value = atoi(vertex_index);
        if (index_value) {
          if (index_value < 0) index_value += vertex_count - 1;
          data->vertex_indices_array[vertex_indices_count] = index_value - 1;
          if (!is_first_index) {
            first_index = index_value - 1;
            is_first_index = 1;
          } else
            data->vertex_indices_array[++vertex_indices_count] =
                index_value - 1;
          vertex_indices_count++;
        }
      }
      data->vertex_indices_array[vertex_indices_count++] = first_index;
    }
  }

  if (line) free(line);
  if (!data->vertex_array[data->vertex_count * 4 - 1] ||
      !data->vertex_indices_array[data->vertex_indices_count * 2 - 1])
    status = ERROR;

  return status;
}
