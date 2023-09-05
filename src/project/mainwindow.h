#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QColorDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QMouseEvent>
#include <QRadioButton>
#include <QSettings>
#include <QWheelEvent>
#include <QtGui>
#include <QtPlugin>

#include "QtGifImage-master/src/gifimage/qgifimage.h"
#include "myglwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();
  ///
  /// \brief save settings from previous session
  ///
  void save_setting();
  ///
  /// \brief loading settings of current session
  ///
  void load_settings();

  ///
  /// \brief sending params from ui to myglwidget
  ///
  void send_params();
  //  void send_changes();

  //    void wheelEvent(QWheelEvent * event);
  //    void mousePressEvent (QMouseEvent * event);
  //    void mouseMoveEvent (QMouseEvent * event);
  //    void mouseReleaseEvent (QMouseEvent * event);

  QString fullname;
  unsigned int num_of_vertexes = 0;
  unsigned int num_of_edges = 0;

  double scale = 1;
  double x_shift = 0;
  double y_shift = 0;
  double z_shift = 0;
  double oz_rotate = 0;
  double oy_rotate = 0;
  double ox_rotate = 0;

  ///
  /// \brief pointer to object of MyGLWidget class
  ///
  MyGLWidget* view;
  QColor back_color;
  QColor line_color;
  QColor vertex_color;

  int projection_type;  // 0-parallel 1-central
  int line_type;        // 0-solid 1-dotted
  int points_type;      // 0-absent 1-box 2-sphere
  int line_width;
  int points_size;

  QGifImage* frame;  // без инициализации, он есть, но ничего не содержит
  QTimer* gif_timer;
  QString gifname;
  int counter = 0;

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

  void on_points_size_spinbox_valueChanged(int arg1);

  void on_absent_point_rb_clicked();

  void on_sphere_point_rb_clicked();

  void on_box_point_rb_clicked();

  void on_line_width_spinbox_valueChanged(int arg1);

  void on_but_reset_clicked();

  void on_Color_button_3_clicked();

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void create_gif_animation();

 private:
  Ui::MainWindow* ui;
  int file_opened = 0;
  QSettings* settings;
};
#endif  // MAINWINDOW_H
