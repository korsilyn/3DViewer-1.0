#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>
#include <QRadioButton>
#include <QSettings>

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
    void save_setting();
    void load_settings();

    QString fullname;
    unsigned int num_of_vertexes = 0;
    unsigned int num_of_polygons = 0;

    double scale = 1;
    double x_shift = 0;
    double y_shift = 0;
    double z_shift = 0;
    double oz_rotate = 0;
    double oy_rotate = 0;
    double ox_rotate = 0;

    MyGLWidget* view;
    QColor back_color;
    QColor line_color;

    int projection_type; //0-parallel 1-central
    int line_type; //0-solid 1-dotted

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

    void on_Color_button_clicked();

    void on_parallel_projection_rb_clicked();

    void on_central_projection_rb_clicked();

    void on_solid_line_rb_clicked();

    void on_dotted_line_rb_clicked();

    void on_Color_button_2_clicked();

private:
    Ui::MainWindow *ui;
    int file_opened = 0;
    QSettings* settings;
};
#endif // MAINWINDOW_H
