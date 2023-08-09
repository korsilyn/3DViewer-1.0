#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QWidget>
#include <QtOpenGLWidgets>
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QtOpenGL>
#include <glu.h>
#include <gl.h>

class MyGLWidget : public QOpenGLWidget
{
public:
    MyGLWidget(QWidget *parent);

protected:
    void initializeGL() override;


    void resizeGL(int w, int h) override;

    void paintGL() override;

};

#endif // MYGLWIDGET_H
