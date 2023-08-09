#include "viewwindow.h"
#include "ui_viewwindow.h"


void ViewWindow::on_pushButton_clicked()
{
//    glWidget->paintGL();
}


ViewWindow::ViewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewWindow)
{
    ui->setupUi(this);
//    glWidget = new MyGLWidget(this);
//    glWidget->initializeGL();

//    glWidget = ui->openGLWidget;
//    glWidget->initializeGL();
}

ViewWindow::~ViewWindow()
{
    delete ui;
}

void ViewWindow::on_spin_x_valueChanged(double arg1)
{
    x_shift = arg1;
}


void ViewWindow::on_spin_y_valueChanged(double arg1)
{
    y_shift = arg1;
}


void ViewWindow::on_spin_z_valueChanged(double arg1)
{
    z_shift = arg1;
}


void ViewWindow::on_slider_ox_sliderMoved(int position)
{
    ox_rotate = position;
}


void ViewWindow::on_slider_oy_sliderMoved(int position)
{
    oy_rotate = position;
}

void ViewWindow::on_slider_oz_sliderMoved(int position)
{
    oz_rotate = position;
}


void ViewWindow::on_scale_slider_sliderMoved(int position)
{
    scale = pow(2, position - 10); // 2^-9 -- 2^10
}




