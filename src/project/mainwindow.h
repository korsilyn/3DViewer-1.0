#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>

#include "myglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString fullname;
    double scale = 1;
    double x_shift = 0;
    double y_shift = 0;
    double z_shift = 0;
    double oz_rotate = 0;
    double oy_rotate = 0;
    double ox_rotate = 0;

    MyGLWidget* view;

private slots:

    void on_spin_x_valueChanged(double arg1);

    void on_spin_y_valueChanged(double arg1);

    void on_spin_z_valueChanged(double arg1);

    void on_slider_ox_sliderMoved(int position);

    void on_slider_oz_sliderMoved(int position);

    void on_slider_oy_sliderMoved(int position);

    void on_scale_slider_sliderMoved(int position);

    void on_but_openFile_clicked();

    void on_but_build_clicked();

private:
    Ui::MainWindow *ui;
    int file_opened = 0;

};
#endif // MAINWINDOW_H
