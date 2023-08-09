#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    view = new MyGLWidget(this);
//    view->show();
    settings = new QSettings(this);
    load_settings();
}

MainWindow::~MainWindow()
{
    save_setting();
    delete ui;
}

void MainWindow::on_but_openFile_clicked()
{
    fullname = QFileDialog::getOpenFileName(this, tr("Open figure"), QLatin1String("*.obj"));
    if (fullname.mid(fullname.lastIndexOf('.')+1) == "obj") {
            ui->label->setText("filename = "+ fullname.mid(fullname.lastIndexOf('/')+1));
            file_opened = 1;
//            num_of_vertexes =
//            num_of_polygons =
            ui->polygons_label->setText(QString::number(num_of_polygons));
            ui->vertexes_label->setText(QString::number(num_of_vertexes));
    } else {
        ui->label->setText("Wrong file");
        file_opened = 0;
    }
}


void MainWindow::on_but_build_clicked()
{
    if (file_opened) {

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


void MainWindow::on_Color_button_clicked()
{
    back_color = QColorDialog::getColor();
#ifdef QT_DEBUG
    QString style = "background: rgb(%1, %2, %3);";
    this->ui->label->setStyleSheet(style.arg(back_color.red()).arg(back_color.green()).arg(back_color.blue()));
#endif
}




void MainWindow::on_parallel_projection_rb_clicked()
{
    ui->central_projection_rb->setChecked(false);
    ui->parallel_projection_rb->setChecked(true);
    projection_type = 0;
}


void MainWindow::on_central_projection_rb_clicked()
{
    ui->parallel_projection_rb->setChecked(false);
    ui->central_projection_rb->setChecked(true);
    projection_type = 1;
}


void MainWindow::on_solid_line_rb_clicked()
{
    ui->dotted_line_rb->setChecked(false);
    ui->solid_line_rb->setChecked(true);
    line_type = 0;
}


void MainWindow::on_dotted_line_rb_clicked()
{
    ui->dotted_line_rb->setChecked(true);
    ui->solid_line_rb->setChecked(false);
    line_type = 1;
}


void MainWindow::on_Color_button_2_clicked()
{
    line_color = QColorDialog::getColor();
}


void MainWindow::save_setting() {

}

void MainWindow::load_settings() {
//    settings->value("title", "Mainform");
}




