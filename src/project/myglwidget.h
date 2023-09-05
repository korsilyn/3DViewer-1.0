#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

//#include <gl.h>
//#include <glu.h>

#include <QMatrix4x4>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QWheelEvent>
#include <QWidget>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
// #include <glew.h>
#include <iostream>

extern "C" {
//    #include "../helpers/s21_3dviewer.h"
#include "../helpers/s21_parse.h"
}

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core {
 public:
  explicit MyGLWidget(QWidget *parent = Q_NULLPTR, QString filename = "");
  ~MyGLWidget() override;

  obj_data data = {0, NULL, 0, NULL};

  int vertexRenderingMode = 0;
  int edgeRenderingMode = 0;
  float vertexSize = 1.0;
  float edgeThickness = 1.0;
  int projectionChanged = 0;
  int projectionType = 1;

  QColor vertexColor = QColor(255, 255, 255, 255);
  QColor edgeColor = QColor(255, 255, 255, 255);
  QColor backColor = QColor(100, 100, 100, 100);

  double scale = 1;
  double x_shift = 0;
  double y_shift = 0;
  double z_shift = 0;
  double oz_rotate = 0;
  double oy_rotate = 0;
  double ox_rotate = 0;

  unsigned int num_of_vertexes = 0;
  unsigned int num_of_edges = 0;

  QString fileFullName;
  std::string filePath;

  //  void afterOpenObj();

  void initializeGL() override;

  ///
  /// \brief mousePressEvent
  /// \param event
  ///
  void mousePressEvent(QMouseEvent *event) override;
  ///
  /// \brief mouseMoveEvent
  /// \param event
  ///
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  QPoint cur_pos;
  QPoint new_pos;
  //

 protected:
  int succsess_reading = 0;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  int flag_not_to_paint = 0;

  QMatrix4x4 modelMatrix;
  QMatrix4x4 projectionMatrix;

  // OpenGL shaders
  GLuint VAO, VBO, EBO;
  QOpenGLShaderProgram shaderProgram;

  const char *vertexSourceCode =
      "#version 330 core\n"
      "layout(location = 0) in vec4 position;\n"
      "uniform mat4 MVPMatrix;\n"
      "void main() {\n"
      "  gl_Position = MVPMatrix * position;\n"
      "}\n";

  const char *fragmentSourceCode =
      "#version 330 core\n"
      "uniform vec4 color;\n"
      "uniform int dashed;\n"
      "out vec4 FragColor;\n"
      "void main() {\n"
      "  if (dashed == 1) {\n"
      "    float dashSize = 0.3;\n"
      "    float gapSize = 0.3;\n"
      "    float t = mod(gl_FragCoord.x, (dashSize + gapSize)) / (dashSize "
      "+ gapSize);\n"
      "    if (t > 0.5) FragColor = color;\n"
      "    else discard;\n"
      "  }\n"
      "  else FragColor = color;\n"
      "}\n";
};

#endif  // MYGLWIDGET_H
