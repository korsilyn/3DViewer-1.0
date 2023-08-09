#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    view = new MyGLWidget(this);
//    view->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_but_openFile_clicked()
{
    fullname = QFileDialog::getOpenFileName(this, tr("Open figure"), QLatin1String("*.obj"));
    if (fullname.mid(fullname.lastIndexOf('.')+1) == "obj") {
            ui->label->setText("filename = "+ fullname.mid(fullname.lastIndexOf('/')+1));
            file_opened = 1;
    } else {
        ui->label->setText("Wrong file");
        file_opened = 0;
    }
}


void MainWindow::on_but_build_clicked()
{
    if (file_opened) {
//        view = new MainWindow();
//        view->show();
    }

}

void MainWindow::on_spin_x_valueChanged(double arg1)
{
    x_shift = arg1;
}


void MainWindow::on_spin_y_valueChanged(double arg1)
{
    y_shift = arg1;
}


void MainWindow::on_spin_z_valueChanged(double arg1)
{
    z_shift = arg1;
}


void MainWindow::on_slider_ox_sliderMoved(int position)
{
    ox_rotate = position;
}


void MainWindow::on_slider_oy_sliderMoved(int position)
{
    oy_rotate = position;
}

void MainWindow::on_slider_oz_sliderMoved(int position)
{
    oz_rotate = position;
}


void MainWindow::on_scale_slider_sliderMoved(int position)
{
    scale = pow(2, position - 10); // 2^-9 -- 2^10
}




