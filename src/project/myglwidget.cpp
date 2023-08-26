#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
  printf("constructor called\n");
}

MyGLWidget::~MyGLWidget() {
  printf("destructor called\n");
  s21_dealloc_data(&data);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteVertexArrays(1, &VAO);
  shaderProgram.removeAllShaders();
}

void MyGLWidget::initializeGL() {
  printf("initializeGL called\n");

  initializeOpenGLFunctions();

//  printf("%p %p %p\n", &VAO, &VBO, &EBO);

  std::string obj_fullname =
      "/home/sellisshe/C8_3DViewer_v1.0-2/src/cube.obj";
  int success = s21_read_obj_file(&data, obj_fullname.c_str());
  if (!success) std::cout << "ERROR::MODEL::LOAD_FAILED\n" << std::endl;

  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexSourceCode);
  printf("%s", shaderProgram.log().toStdString().c_str());
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentSourceCode);
  printf("%s", shaderProgram.log().toStdString().c_str());
  shaderProgram.link();
  printf("%s", shaderProgram.log().toStdString().c_str());
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * data.vertex_count,
               data.vertex_array, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(unsigned int) * 2 * data.vertex_indices_count,
               data.vertex_indices_array, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  shaderProgram.bind();
  glEnable(GL_DEPTH_TEST);
  shaderProgram.release();
}

void MyGLWidget::resizeGL(int w, int h) {
  printf("resizeGL called\n");
  float aspectRatio = static_cast<float>(w) / (h);
  glViewport(0, 0, w, h);
  projectionMatrix.setToIdentity();
  if (projectionType == 0) {
      projectionMatrix.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f); // костыль
  } else {
      projectionMatrix.perspective(60.0f, aspectRatio, 0.1f, 100.0f);
  }
}

void MyGLWidget::paintGL() {
  printf("paintGL called\n");

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //resizeGL(MyGLWidget::width(), MyGLWidget::height());


  modelMatrix.setToIdentity();
  modelMatrix.translate(0.0f, 0.0f, -2.75f);
  modelMatrix.rotate(45.0f, 1.0f, 0.0f, 0.0f);
  modelMatrix.rotate(45.0f, 0.0f, 1.0f, 0.0f);
  shaderProgram.setUniformValue("MVPMatrix", projectionMatrix * modelMatrix);
  //shaderProgram.setUniformValue("projectionMatrix", projectionMatrix);
  shaderProgram.setUniformValue("color", edgeColor);
  shaderProgram.bind();
  glBindVertexArray(VAO);

  if (vertexRenderingMode) glDrawArrays(GL_POINTS, 0, data.vertex_count * 4);
  glDrawElements(GL_LINES, data.vertex_indices_count * 2, GL_UNSIGNED_INT, 0);

//  ///////////
//  printf("GL_VERSION = %s\n", glGetString(GL_VERSION));
//  printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
//  ///////
}
