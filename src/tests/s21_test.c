//#include "s21_3dviewer.h"
#include "s21_parse.h"
#include <stdlib.h>

int main(void) {
	obj_data data = {0};
	//char file[] = "../cube.obj";
	int status = s21_read_obj_file(&data, "/home/korsilyn/sber21/C8_3DViewer_v1.0-2/src/cube.obj");
	if (status == 0) { printf("Amount of vertex: %ld\nArray: ", data.vertex_count);
	for (size_t i = 0; i < data.vertex_count * 3; i++) printf("%lf ", data.vertex_array[i]);
	printf("\n");
	printf("Amount of vertex indices: %ld\nArray: ", data.vertex_indices_count);
	for (size_t i = 0; i < data.vertex_indices_count * 2; i++) printf("%d ", data.vertex_indices_array[i]);
	printf("\n");
	}
	else printf("%d", status);
	s21_dealloc_data(&data);
	return 0;
}

