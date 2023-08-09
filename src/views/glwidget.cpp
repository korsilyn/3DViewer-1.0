#include "glwidget.h"

// Заготовки

void GlWidget::initializeGL() {
	initializeOpenGLFunctions();

	s21_read_obj_file(&data, "../objects/model.obj");
	modelMatrix = glm::mat4(1.0f);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, "../shaders/vertex.glsl", NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, "../shaders/vertex.glsl", NULL);
	glCompileShader(fragmentShader);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * data.vertex_count, data.vertex_array, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &edgeIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 2 * data.vertex_indices_count, data.vertex_indices_array, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glUseProgram(shaderProgram);
	glEnable(GL_DEPTH_TEST);
	glUseProgram(0);
}

void GlWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeIBO);
	if (projectionType == 0) {
		projectionMatrix = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, heigth / 2.0f, -100.0f, 100.0f);
	} else {
		projectionMatrix = glm::perspective(glm::radiands(45), width / height, -100.0f, 100.0f);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}


/*
 * rotate:
 * glm::vec3 rotationAxis = glm::vec3(x, y, z);
 * modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), rotationAxis);
 * move:
 * glm::vec3 moveAxis = glm::vec3(x, y, z);
 * modelMatrix = glm::translate(modelMatrix, moveAxis);
 * scale:
 * glm:vec3 scaleAxix = glm::vec3(scale, scale, scale);
 * modelMatrix = glm::scale(modelMatrix, scaleAxis);
