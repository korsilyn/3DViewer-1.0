#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QtOpenGLWidgets>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <glu.h>
#include <gl.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>	

extern "C" {
	#include "../helpers/s21_3dviewer.h"
	#include "../helpers/s21_parse.h"
}

class MyGLWidget : public QOpenGLWidget
{
public:
    explicit MyGLWidget(QWidget *parent = Q_NULLPTR);

    obj_data data;
    int vertexRenderingMode;
    int edgeRenderingMode;
    float vertexSize;
    float edgeThickness;
    int projectionType;

    // OpenGL shaders
    GLuint vertexVBO;
    GLuint edgeIBO;
    GLuint shaderProgram;
    glm::mat4 modelMatrix;
    glm::mat4 projectionMatrix;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

private:
    ~MyGLWidget() override;
};

#endif // MYGLWIDGET_H
