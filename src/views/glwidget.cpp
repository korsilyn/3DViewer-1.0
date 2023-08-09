#include "glwidget.h"

// Заготовки

~GlWidget() { 

void initializeGL() {
	initializeOpenGLFunctions();
	glEnable(GL_DEPTH_TEST);
}
