//#include "s21_3dviewer.h"
#include "s21_parse.h"

int main(void) {
	obj_data data = {0};
	char file[] = "big_test.obj";
	int status = s21_read_obj_file(&data, file);
	if (status == 0) { printf("Amount of vertex: %ld\n", data.vertex_count);
	printf("Amount of vertex indices: %ld\n", data.vertex_indices_count); }
	else printf("%d", status);
	s21_dealloc_data(&data);
	return 0;
}

