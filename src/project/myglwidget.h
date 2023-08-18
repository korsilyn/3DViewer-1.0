#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QtOpenGLWidgets>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <glu.h>
#include <gl.h>
//#include <glew.h>
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

extern "C" {
//    #include "../helpers/s21_3dviewer.h"
    #include "../helpers/s21_parse.h"
}

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    explicit MyGLWidget(QWidget *parent = Q_NULLPTR);
    ~MyGLWidget() override;
    obj_data data;
    int vertexRenderingMode = 1;
    int edgeRenderingMode = 0;
    float vertexSize = 1.0;
    float edgeThickness = 1.0;
    int projectionType = 0;
    QString fileFullName;
    std::string filePath;

    glm::mat4 modelMatrix;
    glm::mat4 projectionMatrix;

    QColor vertexColor = QColor(255,255,255,255);
    QColor edgeColor = QColor(255,255,255,255);

    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void doTheThing();

protected:


private:
    std::string ReadShaderFromFile(const char *file);


    // OpenGL shaders
    GLuint vertexVBO;
    GLuint edgeIBO;
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;

};

#endif // MYGLWIDGET_H
