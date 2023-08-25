#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
  printf("constructor called\n");
}

MyGLWidget::~MyGLWidget() {
  printf("destructor called\n");
  s21_dealloc_data(&data);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
}

void MyGLWidget::initializeGL() {
  printf("initializeGL called\n");

  initializeOpenGLFunctions();

//  printf("%p %p %p\n", &VAO, &VBO, &EBO);


  std::string obj_fullname =
      "/Users/sabrahar/Desktop/C8_3DViewer_v1.0-2/src/objects/cube.obj";
  int success = s21_read_obj_file(&data, (char *)obj_fullname.c_str());
  if (!success) std::cout << "ERROR::MODEL::LOAD_FAILED\n" << std::endl;

  modelMatrix = glm::mat4(1.0f);  
  viewMatrix = glm::mat4(1.0f);
  viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -2.5f));

  std::string vertexShaderCode = ReadShaderFromFile(
      "/Users/sabrahar/Desktop/C8_3DViewer_v1.0-2/src/shaders/vertex.glsl");
  std::string fragmentShaderCode = ReadShaderFromFile(
      "/Users/sabrahar/Desktop/C8_3DViewer_v1.0-2/src/shaders/fragment.glsl");
  const char *vertexShaderSource = vertexShaderCode.c_str();
  const char *fragmentShaderSource = fragmentShaderCode.c_str();

  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  printf("%s", shaderProgram.log());
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  printf("%s", shaderProgram.log());

  shaderProgram.link();
  printf("%s", shaderProgram.log());
  shaderProgram.bind();

  glGenBuffers(1, &VBO); 
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * data.vertex_count,
               data.vertex_array, GL_STATIC_DRAW);
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(GLuint) * 2 * data.vertex_indices_count,
               data.vertex_indices_array, GL_STATIC_DRAW);

  GLuint positionLoc = shaderProgram.attributeLocation("position");
  glEnableVertexAttribArray(positionLoc);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPoinder(positionLoc, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

  glEnable(GL_DEPTH_TEST);
  shaderProgram.release();
}

void MyGLWidget::resizeGL(int w, int h) {
  // Update projection matrix and other size related settings:
  //        m_projection.setToIdentity();
  //        m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
  //        ...
  w;
  h;
}

void MyGLWidget::paintGL() {
  printf("paintGL called\n");

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  shaderProgram.bind();

  double width = 570;
  double height = 450;
  if (projectionType == 0) {
    projectionMatrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);

  } /*else {
      projectionMatrix = glm::perspective(glm::radians(45.0), (float)width /
  (float)height, 0.1f, 100.0f);
  }*/

  glUseProgram(shaderProgram);

  shaderProgram.setUniformValue("modelMatrix", modelMatrix);
  shaderProgram.setUniformValue("viewMatrix", viewMatrix);
  shaderProgram.setUniformValue("projectionMatrix", projectionMatrix);
  shaderProgram.setUniformValue("color", edgeColor);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  if (vertexRenderingMode) glDrawArrays(GL_POINTS, 0, data.vertex_count);
  glDrawElements(GL_LINES, data.vertex_indices_count * 2, GL_UNSIGNED_INT, 0);


//  ///////////
//  printf("GL_VERSION = %s\n", glGetString(GL_VERSION));
//  printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
//  ///////
  shaderProgram.release();
}

void MyGLWidget::doTheThing() {
  printf("doTheThing called\n");
  this->paintGL();
}

std::string MyGLWidget::ReadShaderFromFile(const char *file) {
  std::string shaderCode;
  std::ifstream shaderFile(file);
  if (shaderFile.is_open()) {
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderCode = shaderStream.str();
    shaderFile.close();
  } else
    std::cerr << "Unable to open file!" << std::endl;
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
