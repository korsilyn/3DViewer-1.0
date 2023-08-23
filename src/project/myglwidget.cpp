#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget{parent} {
  printf("constructor called\n");
}

MyGLWidget::~MyGLWidget() {
  printf("destructor called\n");
  s21_dealloc_data(&data);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(shaderProgram);
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
  viewMatrix = glm::translate(viewMatrix, glm::vec3(0.0f, 0.0f, -3.0f));

  std::string vertexShaderCode = ReadShaderFromFile(
      "/Users/sabrahar/Desktop/C8_3DViewer_v1.0-2/src/shaders/vertex.glsl");
  std::string fragmentShaderCode = ReadShaderFromFile(
      "/Users/sabrahar/Desktop/C8_3DViewer_v1.0-2/src/shaders/fragment.glsl");
  const char *vertexShaderSource = vertexShaderCode.c_str();
  const char *fragmentShaderSource = fragmentShaderCode.c_str();

  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
              << infoLog << std::endl;
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
              << infoLog << std::endl;
  }
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * data.vertex_count,
               data.vertex_array, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               sizeof(GLint) * 2 * data.vertex_indices_count,
               data.vertex_indices_array, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, (GLsizei)(4 * sizeof(float)), //sizeof(float) == sizeof(GLFloat)
                        (void *)0);

  //glBindBuffer(GL_ARRAY_BUFFER, 0);
  //glBindVertexArray(0);

  glUseProgram(shaderProgram);
  glEnable(GL_DEPTH_TEST);
  glUseProgram(0);
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


  double width = 570;
  double height = 450;
  if (projectionType == 0) {
    projectionMatrix = glm::ortho(0.0f, (float)width, (float)height, 0.0f, -1.0f, 1.0f);

  } /*else {
      projectionMatrix = glm::perspective(glm::radians(45.0), (float)width /
  (float)height, 0.1f, 100.0f);
  }*/

  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  // set uniforms
  GLint modelMatrixLoc = glGetUniformLocation(shaderProgram, "modelMatrix");
  glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
  GLint projectionMatrixLoc =
      glGetUniformLocation(shaderProgram, "projecionMatrix");
  glUniformMatrix4fv(projectionMatrixLoc, 1, GL_FALSE,
                     glm::value_ptr(projectionMatrix));
  GLint viewMatrixLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
  glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));

  /*GLint vertexRenderingModeLoc =
      glGetUniformLocation(shaderProgram, "vertexRenderingMode");
  glUniform1i(vertexRenderingModeLoc, vertexRenderingMode);
  GLint edgeRenderingModeLoc =
      glGetUniformLocation(shaderProgram, "edgeRenderingMode");
  glUniform1i(edgeRenderingModeLoc, edgeRenderingMode);
  GLint vertexSizeLoc = glGetUniformLocation(shaderProgram, "vertexSize");
  glUniform1f(vertexSizeLoc, vertexSize);
  GLint edgeThicknessLoc = glGetUniformLocation(shaderProgram, "edgeThickness");
  glUniform1f(edgeThicknessLoc, edgeThickness);

  GLint vertexColorLoc = glGetUniformLocation(shaderProgram, "vertexColor");
  glUniform4f(vertexColorLoc, vertexColor.red(), vertexColor.green(),
              vertexColor.blue(), vertexColor.alpha()); */

  GLint edgeColorLoc = glGetUniformLocation(shaderProgram, "edgeColor");
  glUniform4f(edgeColorLoc, edgeColor.red(), edgeColor.green(),
              edgeColor.blue(), edgeColor.alpha());

  if (vertexRenderingMode) glDrawArrays(GL_POINTS, 0, data.vertex_count);
  glDrawElements(GL_LINES, data.vertex_indices_count * 2, GL_UNSIGNED_INT, 0);


//  ///////////
//  printf("GL_VERSION = %s\n", glGetString(GL_VERSION));
//  printf("GL_VENDOR = %s\n", glGetString(GL_VENDOR));
//  ///////
  //glUseProgram(0);
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

void MyGLWidget::doTheThing() {
  printf("doTheThing called\n");
  this->paintGL();
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
