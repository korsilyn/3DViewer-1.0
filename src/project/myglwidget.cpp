#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent, QString filename)
    : QOpenGLWidget{parent} {
  printf("constructor called\n");
  fileFullName = filename;
  this->update();
  this->update();
  succsess_reading =
      s21_read_obj_file(&data, fileFullName.toStdString().c_str());
  num_of_vertexes = data.vertex_count;
  num_of_edges = data.vertex_indices_count;
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

  //  std::string obj_fullname = fileFullName.toStdString();

  //  std::string obj_fullname  =
  //  "/Users/sabrahar/Desktop/C8_3DViewer_v1.0-2/src/objects/cat.obj";
  printf("--%s\n", fileFullName.toStdString().c_str());

  if (!succsess_reading)
    std::cout << "ERROR::MODEL::LOAD_FAILED\n" << std::endl;

  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                        vertexSourceCode);
  printf("%s", shaderProgram.log().toStdString().c_str());
  shaderProgram.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                        fragmentSourceCode);
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

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  shaderProgram.bind();
  glEnable(GL_DEPTH_TEST);
  shaderProgram.release();

  // paintGL();
}

void MyGLWidget::resizeGL(int w, int h) {
  printf("resizeGL called\n");
  float aspectRatio = static_cast<float>(w) / (h);
  glViewport(0, 0, w, h);
  projectionMatrix.setToIdentity();
  if (projectionType == 0) {
    projectionMatrix.ortho(-w / 150.0f, w / 150.0f, -h / 150.0f, h / 150.0f,
                           0.1f, 100.0f);
  } else {
    projectionMatrix.perspective(60.0f, aspectRatio, 0.1f, 100.0f);
  }
}

void MyGLWidget::paintGL() {
  //  printf("paintGL called\n");

  glClearColor(backColor.redF(), backColor.greenF(), backColor.blueF(),
               backColor.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (projectionChanged) {
    resizeGL(MyGLWidget::width(), MyGLWidget::height());
    projectionChanged = !projectionChanged;
  }

  modelMatrix.setToIdentity();
  modelMatrix.translate(x_shift, y_shift, -3.0f + z_shift);
  modelMatrix.rotate(ox_rotate, 1.0f, 0.0f, 0.0f);
  modelMatrix.rotate(oy_rotate, 0.0f, 1.0f, 0.0f);
  modelMatrix.rotate(oz_rotate, 0.0f, 0.0f, 1.0f);
  modelMatrix.scale(scale);

  shaderProgram.bind();
  glBindVertexArray(VAO);
  shaderProgram.setUniformValue("MVPMatrix", projectionMatrix * modelMatrix);
  shaderProgram.setUniformValue("dashed", edgeRenderingMode);  // new
  glPointSize(vertexSize);
  shaderProgram.setUniformValue("color", vertexColor);
  glLineWidth(edgeThickness);  // new
  if (vertexRenderingMode == 1) {
    glDrawArrays(GL_POINTS, 0, data.vertex_count * 4);
  } else if (vertexRenderingMode == 2) {  // new
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, data.vertex_count * 4);
    glDisable(GL_POINT_SMOOTH);
    glDisable(GL_BLEND);
  }
  shaderProgram.setUniformValue("color", edgeColor);
  glDrawElements(GL_LINES, data.vertex_indices_count * 2, GL_UNSIGNED_INT, 0);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *event) {
  new_pos = QPoint(event->globalPosition().toPoint() - cur_pos);
  if (event->buttons() & Qt::RightButton) {
    ox_rotate += -new_pos.y() / 100;
    oy_rotate += new_pos.x() / 100;
  }
  update();
}

void MyGLWidget::wheelEvent(QWheelEvent *event) {
  QPoint YouSpinMeRightRound = event->angleDelta() / 240;
  //  double step = normalize_coef / 10;
  //  double scale_tmp = scale_val;
  //  if ((int)(scale_val + numDegrees.y() * step) > 0) {
  //    scale_val += numDegrees.y() * step;
  //    scale(&this->data, scale_val / scale_tmp);
  //    update();
  //  }
  scale += YouSpinMeRightRound.y();
  if (scale > 0.01 && scale < 100) {
    update();
  }
}

void MyGLWidget::mousePressEvent(QMouseEvent *event) {
  cur_pos = event->globalPosition().toPoint();
}
