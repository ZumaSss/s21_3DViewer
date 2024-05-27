#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <mainwindow.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

extern "C" {
#include <modules.h>
}

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent = 0);
  ~GLWidget();
  model_data obj = {0, NULL, 0, NULL};
  bool mode = false;
  bool stipple = false;
  int points_mode = 0;
  float bg_r = 0, bg_g = 0, bg_b = 0;
  float lines_r = 1, lines_g = 1, lines_b = 1;
  float points_r = 1, points_g = 1, points_b = 1;
  int width = 1;
  int size_points = 1;

  void read_file();
  void move_x(double dx);
  void move_y(double dx);
  void move_z(double dx);
  void rotate_x(double dx);
  void rotate_y(double dx);
  void rotate_z(double dx);
  void model_scale(double dx);

  void set_mode(bool p_mode);
  void set_bg_color(QColor color);
  void set_lines_color(QColor color);
  void set_stipple(bool stipple_mode);
  void set_width(bool less_or_more);
  void set_points_color(QColor color);
  void set_size_points(bool less_or_more);
  void set_points_mode(int p_mode);

  void load_size_points(int size_p);
  void load_width(int l_width);

 signals:
  void send_filename(QString);
  void send_info_obj(model_data);

 protected:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
};

#endif  // GLWIDGET_H
