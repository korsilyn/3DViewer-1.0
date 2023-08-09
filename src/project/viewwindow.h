#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QMainWindow>
#include <QtMath>
#include <QWidget>
#include "myglwidget.h"


namespace Ui {
class ViewWindow;
}

class ViewWindow : public QMainWindow //, private QOpenGLWidget
{
    Q_OBJECT

public:
    explicit ViewWindow(QWidget *parent = nullptr);
    ~ViewWindow();

private slots:
    void on_spin_x_valueChanged(double arg1);

    void on_spin_y_valueChanged(double arg1);

    void on_spin_z_valueChanged(double arg1);

    void on_slider_ox_sliderMoved(int position);

    void on_slider_oz_sliderMoved(int position);

    void on_slider_oy_sliderMoved(int position);

    void on_scale_slider_sliderMoved(int position);

    void on_pushButton_clicked();

private:
    MyGLWidget* glWidget;
    Ui::ViewWindow *ui;

};

#endif // VIEWWINDOW_H
