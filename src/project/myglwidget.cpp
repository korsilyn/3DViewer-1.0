#include "myglwidget.h"


    MyGLWidget::MyGLWidget(QWidget *parent) : QOpenGLWidget(parent) {
    }

    void MyGLWidget::initializeGL()
    {
        // Set up the rendering context, load shaders and other resources, etc.:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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
        // Draw the scene:
        QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
        f->glClear(GL_COLOR_BUFFER_BIT);

    }

