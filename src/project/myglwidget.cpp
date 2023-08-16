#include "myglwidget.h"


    MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    }

	MyGLWidget::~MyGLWidget() {
		s21_dealloc_data(&data);
		glDeleteProgram(shaderProgram);
	}

    void MyGLWidget::initializeGL()
    {
        initializeOpenGLFunctions();

	s21_read_obj_file(&data, "../objects/model.obj");
	modelMatrix = glm::mat4(1.0f);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	std::string vertexShaderCode = ReadShaderFromFile("../shaders/vertex.glsl");
	std::string fragmentShaderCode = ReadShaderFromFile("../shaders/fragment.glsl");
	const char *vertexShaderSource = vertexShaderCode.c_str();
	const char *fragmentShaderSource = fragmentShaderCode.c_str();

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
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

    void MyGLWidget::resizeGL(int w, int h)
    {
        // Update projection matrix and other size related settings:
//        m_projection.setToIdentity();
//        m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
//        ...
    }

    void MyGLWidget::paintGL()
    {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shaderProgram);
	if (projectionType == 0) {
		projectionMatrix = glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, heigth / 2.0f, -100.0f, 100.0f);
	} else {
		projectionMatrix = glm::perspective(glm::radiands(45), width / height, -100.0f, 100.0f);
	}

	// set uniforms
	GLint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
	glUniformMatrix4fv(modelMatrixLoc, GL_FALSE, glm::value_ptr(modelMatrix));
	GLint projectionMatrixLoc = glGetUniformLocation(shaderProgram, "projecionMatrix");
	glUniformMatrix4fv(projectionMatrixLoc, GL_FALSE, glm::value_ptr(projectionMatrix));
	GLint vertexRenderingModeLoc = glGetUniformLocation(shaderProgram, "vertexRenderingMode");
	glUniformMatrix1i(vertexRenderingModeLoc, vertexRenderingMode);
	GLint edgeRenderingModeLoc = glGetUniformLocation(shaderProgram, "edgeRenderingMode");
	glUniformMatrix1i(edgeRenderingModeLoc, edgeRenderingMode);
	GLint vertexSizeLoc = glGetUniformLocation(shaderProgram, "vertexSize");
	glUniformMatrix1f(vertexSizeLoc, vertexSize);
	GLint edgeThicknessLoc = glGetUniformLocation(shaderProgram, "edgeThickness");
	glUniformMatrix1f(edgeThicknessLoc, edgeThickness);
	/*
	* GLint vertexColorLoc = glGetUniformLocation(shaderProgram, "vertexColor");
	* glUniformMatrix4f(vertexColorLoc, vertexColor.r, vertexColor.g, vertexColor.b, vertexColor.a);
	* GLint edgeColorLoc = glGetUniformLocation(shaderProgram, "edgeColor");
	* glUniformMatrix4f(edgeColorLoc, edgeColor.r, edgeColor.g, edgeColor.b, edgeColor.a);
	*/

	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, edgeIBO);
	
	GLint positionAttribLoc = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(positionAttribLoc);

	glVertexAttribPointer(positionAttribLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
	if (vertexRenderingMode) glDrawArrays(GL_POINTS, 0, data.vertex_count);
	glDrawElements(GL_LINES, data.vertex_indices_count * 2, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(positionAttribLoc);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
    }

std::string ReadShaderFromFile(const char *file) {
	std::string shaderCode;
	std::ifstream shaderFile(file);
	if(shaderFile.is_open()) {
		std::stringstream shaderStream;
		shaderStream << shaderFuke.rdbuf();
		shaderCode = shaderStream.str();
		shaderFile.close();
	}
	else std::cerr << "Unable to open file!" << std::endl;
	return shaderCode;
}

/*
 * rotate:
 * glm::vec3 rotationaxis = glm::vec3(x, y, z);
 * modelmatrix = glm::rotate(modelmatrix, glm::radians(angle), rotationaxis);
 * move:
 * glm::vec3 moveaxis = glm::vec3(x, y, z);
 * modelmatrix = glm::translate(modelmatrix, moveaxis);
 * scale:
 * glm:vec3 scaleaxix = glm::vec3(scale, scale, scale);
 * modelmatrix = glm::scale(modelmatrix, scaleaxis);
 */
