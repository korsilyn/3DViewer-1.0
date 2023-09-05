#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  //    ui->centralwidget->setFixedSize(950,500);
  this->setFixedSize(950, 550);
  view = ui->openGLWidget;
  settings = new QSettings(this);
  load_settings();
  //    QWheelEvent* qwheel = new QWheelEvent(QWheelEvent::)
  //    delete view;
  QString a = QDir::currentPath()
                  .mid(0, QDir::currentPath().lastIndexOf('/') - 1)
                  .toStdString()
                  .c_str();
  a = a.mid(0, a.lastIndexOf('/') - 1);
  a = a.mid(0, a.lastIndexOf('/') - 1);
  a = a.mid(0, a.lastIndexOf('/'));
  a = a + "/objects/cat.obj";
  view->fileFullName = a;

  gif_timer = new QTimer(this);
  connect(gif_timer, SIGNAL(timeout()), this, SLOT(create_gif_animation()));
}

MainWindow::~MainWindow() {
  save_setting();
  delete settings;
  delete ui;
}

void MainWindow::send_params() {
  view->scale = scale;
  view->x_shift = x_shift;
  view->y_shift = y_shift;
  view->z_shift = z_shift;
  view->oz_rotate = oz_rotate;
  view->oy_rotate = oy_rotate;
  view->ox_rotate = ox_rotate;

  view->vertexRenderingMode = points_type;
  view->edgeRenderingMode = line_type;
  view->vertexSize = points_size;
  view->edgeThickness = line_width;
  if (view->projectionType != projection_type)
    view->projectionChanged = 1;  // tmp
  view->projectionType = projection_type;

  view->vertexColor = vertex_color;
  view->edgeColor = line_color;
  view->backColor = back_color;
}

void MainWindow::on_but_openFile_clicked() {
  QString a = QDir::currentPath()
                  .mid(0, QDir::currentPath().lastIndexOf('/') - 1)
                  .toStdString()
                  .c_str();
  //  ui->label->setText(a);
  //  a = a.mid(0, a.lastIndexOf('/') - 1);
  //  ui->label_10->setText(a);
  //  a = a.mid(0, a.lastIndexOf('/'));
  //  ui->label_11->setText(a);

  fullname = QFileDialog::getOpenFileName(this, tr("Open .obj file:"), a,
                                          tr("Obj Files (*.obj)"));

  view->update();
  view->update();
  if (fullname.mid(fullname.lastIndexOf('.') + 1) == "obj") {
    ui->label->setText("filename = " +
                       fullname.mid(fullname.lastIndexOf('/') + 1));
    file_opened = 1;

    if (view) {
      ui->Layout_for_glwidget->removeWidget(view);
      delete view;
    }
    view = new MyGLWidget(this, fullname);

    ui->Layout_for_glwidget->addWidget(view, 0);

    view->fileFullName = fullname;
    view->filePath =
        QString(fullname.mid(0, fullname.lastIndexOf('/') - 1)).toStdString();
    view->filePath =
        QString(fullname.mid(0, fullname.lastIndexOf('/') - 1)).toStdString();
    printf("%s\n", view->fileFullName.toStdString().c_str());

    num_of_edges = view->num_of_edges;
    num_of_vertexes = view->num_of_vertexes;
    ui->polygons_label->setText(QString::number(num_of_edges));
    ui->vertexes_label->setText(QString::number(num_of_vertexes));

  } else {
    ui->label->setText("Wrong file");
    file_opened = 0;
  }
}

void MainWindow::on_but_build_clicked() {
  send_params();
  //    view->afterOpenObj();
  view->update();

  num_of_edges = view->num_of_edges;
  num_of_vertexes = view->num_of_vertexes;
  ui->polygons_label->setText(QString::number(num_of_edges));
  ui->vertexes_label->setText(QString::number(num_of_vertexes));
}

void MainWindow::on_spin_x_valueChanged(double arg1) {
  x_shift = arg1;
  send_params();
  view->update();
}

void MainWindow::on_spin_y_valueChanged(double arg1) {
  y_shift = arg1;
  send_params();
  view->update();
}

void MainWindow::on_spin_z_valueChanged(double arg1) {
  z_shift = arg1;
  send_params();
  view->update();
}

void MainWindow::on_slider_ox_sliderMoved(int position) {
  ox_rotate = position / 6.283;
  send_params();
  view->update();
}

void MainWindow::on_slider_oy_sliderMoved(int position) {
  oz_rotate = position / 6.283;
  send_params();
  view->update();
}

void MainWindow::on_slider_oz_sliderMoved(int position) {
  oy_rotate = position / 6.283;  // tut kostil
  send_params();
  view->update();
}

void MainWindow::on_scale_slider_sliderMoved(int position) {
  scale = pow(1.2, position - 10);  // 1.2^-9 -- 1.2^10
  send_params();
  view->update();
}

void MainWindow::on_Color_button_clicked() {
  back_color = QColorDialog::getColor();
  view->backColor = back_color;
  //  view->afterOpenObj();
  view->update();
}

//////////////settings

void MainWindow::save_setting() {
  settings->setValue("projection_type", projection_type);
  settings->setValue("line_type", line_type);

  settings->setValue("line_width", line_width);

  settings->setValue("points_type", points_type);
  settings->setValue("points_size", points_size);

  settings->setValue("back_color", back_color);
  settings->setValue("line_color", line_color);
  settings->setValue("vertex_color", vertex_color);

  settings->setValue("fullname", fullname);
}

void MainWindow::load_settings() {
  projection_type = settings->value("projection_type").toInt();
  line_type = settings->value("line_type").toInt();
  line_width = settings->value("line_width").toInt();

  points_type = settings->value("points_type").toInt();
  points_size = settings->value("points_size").toInt();

  back_color = settings->value("back_color").value<QColor>();
  line_color = settings->value("line_color").value<QColor>();
  vertex_color = settings->value("vertex_color").value<QColor>();

  fullname = settings->value("fullname").toString();

  switch (projection_type) {
    case 0:
      ui->parallel_projection_rb->setChecked(true);
      ui->central_projection_rb->setChecked(false);
      break;
    case 1:
      ui->parallel_projection_rb->setChecked(false);
      ui->central_projection_rb->setChecked(true);
    default:
      break;
  }

  switch (line_type) {
    case 0:
      ui->solid_line_rb->setChecked(true);
      ui->dotted_line_rb->setChecked(false);
      break;
    case 1:
      ui->solid_line_rb->setChecked(false);
      ui->dotted_line_rb->setChecked(true);
      break;
    default:
      break;
  }

  switch (points_type) {
    case 0:
      ui->absent_point_rb->setChecked(true);
      ui->box_point_rb->setChecked(false);
      ui->sphere_point_rb->setChecked(false);
      break;
    case 1:
      ui->absent_point_rb->setChecked(false);
      ui->box_point_rb->setChecked(true);
      ui->sphere_point_rb->setChecked(false);
      break;
    case 2:
      ui->absent_point_rb->setChecked(false);
      ui->box_point_rb->setChecked(false);
      ui->sphere_point_rb->setChecked(true);
      break;
    default:
      break;
  }

  ui->line_width_spinbox->setValue(line_width);
  ui->points_size_spinbox->setValue(points_size);

  //  ui->label->setText("filename = " +
  //                     fullname.mid(fullname.lastIndexOf('/') + 1));
  //  file_opened = 1;
  //  view->fileFullName = fullname;
  num_of_vertexes = view->data.vertex_count;
  num_of_edges = view->data.vertex_indices_count;
  ui->polygons_label->setText(QString::number(num_of_edges));
  ui->vertexes_label->setText(QString::number(num_of_vertexes));
}

//////////////settings

void MainWindow::on_parallel_projection_rb_clicked() {
  ui->central_projection_rb->setChecked(false);
  ui->parallel_projection_rb->setChecked(true);
  projection_type = 0;
  send_params();
  view->update();
}

void MainWindow::on_central_projection_rb_clicked() {
  ui->parallel_projection_rb->setChecked(false);
  ui->central_projection_rb->setChecked(true);
  projection_type = 1;
  send_params();
  view->update();
}

void MainWindow::on_solid_line_rb_clicked() {
  ui->dotted_line_rb->setChecked(false);
  ui->solid_line_rb->setChecked(true);
  line_type = 0;
  send_params();
  view->update();
}

void MainWindow::on_dotted_line_rb_clicked() {
  ui->dotted_line_rb->setChecked(true);
  ui->solid_line_rb->setChecked(false);
  line_type = 1;
  send_params();
  view->update();
}

void MainWindow::on_Color_button_2_clicked() {
  line_color = QColorDialog::getColor();
  view->edgeColor = line_color;
  send_params();
  view->update();
}

void MainWindow::on_Color_button_3_clicked() {
  vertex_color = QColorDialog::getColor();
  view->vertexColor = vertex_color;
  send_params();
  view->update();
}

void MainWindow::on_points_size_spinbox_valueChanged(int arg1) {
  points_size = arg1;
  send_params();
  view->update();
}

void MainWindow::on_absent_point_rb_clicked() {
  points_type = 0;
  send_params();
  view->update();
}

void MainWindow::on_sphere_point_rb_clicked() {
  points_type = 2;
  send_params();
  view->update();
}

void MainWindow::on_box_point_rb_clicked() {
  points_type = 1;
  send_params();
  view->update();
}

void MainWindow::on_line_width_spinbox_valueChanged(int arg1) {
  line_width = arg1;
  send_params();
  view->update();
}

void MainWindow::on_but_reset_clicked() {
  /// gui
  ui->line_width_spinbox->setValue(1);
  ui->points_size_spinbox->setValue(1);
  ui->scale_slider->setValue(10);
  ui->spin_x->setValue(0);
  ui->spin_y->setValue(0);
  ui->spin_z->setValue(0);
  ui->slider_ox->setValue(0);
  ui->slider_oy->setValue(0);
  ui->slider_oz->setValue(0);
  ui->central_projection_rb->setChecked(true);
  ui->solid_line_rb->setChecked(true);
  ui->sphere_point_rb->setChecked(true);
  /// values
  scale = 1;
  x_shift = 0;
  y_shift = 0;
  z_shift = 0;
  oz_rotate = 0;
  oy_rotate = 0;
  ox_rotate = 0;
  projection_type = 1;
  line_type = 0;
  points_type = 2;
  line_width = 1;
  points_size = 1;
  send_params();
  view->update();
}

void MainWindow::on_pushButton_clicked() {
  QString filename = QFileDialog::getSaveFileName(
      this, "Save File", getenv("HOME"), "Image (*.jpg *.jpeg *.bmp)");
  if (!filename.endsWith(".jpg") && !filename.endsWith(".jpeg") &&
      !filename.endsWith(".bmp")) {
    filename.append(".jpg");
  }
  QImage image = view->grabFramebuffer();
  if (!image.save(filename, "JPG")) {
    QMessageBox::warning(this, "Save Image", "Error saving image.");
  }
}

void MainWindow::create_gif_animation() {
  QImage image = view->grabFramebuffer();
  QSize gif_size(640, 480);
  QImage new_image = image.scaled(gif_size);
  frame->addFrame(new_image);

  if (counter == 50) {  // если последний вызов
    frame->save(gifname);
    gif_timer->stop();
    counter = 0;
    frame = NULL;
  }
  counter++;
}

void MainWindow::on_pushButton_2_clicked() {
  gifname = QFileDialog::getSaveFileName(this, "Save File", getenv("HOME"),
                                         "Image (*.gif)");
  if (!gifname.endsWith(".gif")) {
    gifname.append(".gif");
  }
  frame = new QGifImage();

  gif_timer->setInterval(100);
  gif_timer->start();
}
