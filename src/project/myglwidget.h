#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <gl.h>
#include <glu.h>

#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
// #include <glew.h>
#include <fstream>
#include <iostream>
#include <sstream>

#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

extern "C" {
//    #include "../helpers/s21_3dviewer.h"
#include "../helpers/s21_parse.h"
}

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
 public:
  explicit MyGLWidget(QWidget *parent = Q_NULLPTR);
  ~MyGLWidget() override;
  obj_data data = {0, NULL, 0, NULL};
  int vertexRenderingMode = 1;
  int edgeRenderingMode = 0;
  float vertexSize = 1.0;
  float edgeThickness = 1.0;
  int projectionType = 0;
  QString fileFullName;
  std::string filePath;

  glm::mat4 modelMatrix;
  glm::mat4 viewMatrix;
  glm::mat4 projectionMatrix;

  QColor vertexColor = QColor(255, 255, 255, 255);
  QColor edgeColor = QColor(255, 255, 255, 255);

  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void doTheThing();

 protected:
 private:
  std::string ReadShaderFromFile(const char *file);

  // OpenGL shaders
  GLuint VAO, VBO, EBO;
  GLuint shaderProgram;
  GLuint vertexShader;
  GLuint fragmentShader;
};

#endif  // MYGLWIDGET_H
