#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent) {}

GLWidget::~GLWidget() { memory_free(&obj); }

void GLWidget::read_file() {
  const QString file_name =
      QFileDialog::getOpenFileName(this, "Choose the .obj file", "../../tests");
  if (!file_name.isEmpty()) {
    QByteArray byteArray = file_name.toLatin1();
    char* file_name_c = byteArray.data();

    int parse_res = file_obj_parser(file_name_c, &obj);
    if (parse_res)
      QMessageBox::information(this, "Error", "Ошибка при чтении файла!");
    else {
      emit send_filename(file_name);
      emit send_info_obj(obj);
      update();
    }
  }
}

void GLWidget::move_x(double dx) {
  move_X(&obj, dx);
  update();
}

void GLWidget::move_y(double dx) {
  move_Y(&obj, dx);
  update();
}

void GLWidget::move_z(double dx) {
  move_Z(&obj, dx);
  update();
}

void GLWidget::rotate_x(double dx) {
  rotate_X(&obj, dx);
  update();
}

void GLWidget::rotate_y(double dx) {
  rotate_Y(&obj, dx);
  update();
}

void GLWidget::rotate_z(double dx) {
  rotate_Z(&obj, dx);
  update();
}

void GLWidget::model_scale(double dx) {
  scale(&obj, dx);
  update();
}

void GLWidget::set_mode(bool p_mode) {
  mode = p_mode;
  update();
}

void GLWidget::set_bg_color(QColor color) {
  color.getRgbF(&bg_r, &bg_g, &bg_b);
  update();
}

void GLWidget::set_lines_color(QColor color) {
  color.getRgbF(&lines_r, &lines_g, &lines_b);
  update();
}

void GLWidget::set_stipple(bool stipple_mode) {
  stipple = stipple_mode;
  update();
}

void GLWidget::set_width(bool less_or_more) {
  if (less_or_more)
    width++;
  else {
    if (width > 1) width--;
  }
  update();
}

void GLWidget::set_points_color(QColor color) {
  color.getRgbF(&points_r, &points_g, &points_b);
  update();
}

void GLWidget::set_size_points(bool less_or_more) {
  if (less_or_more)
    size_points++;
  else {
    if (size_points > 1) size_points--;
  }
  update();
}

void GLWidget::set_points_mode(int p_mode) {
  points_mode = p_mode;
  update();
}

void GLWidget::load_size_points(int size_p) {
  size_points = size_p;
  update();
}

void GLWidget::load_width(int l_width) {
  width = l_width;
  update();
}

void GLWidget::initializeGL() {
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void GLWidget::paintGL() {
  glClearColor(bg_r, bg_g, bg_b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (mode)
    glFrustum(-1, 1, -1, 1, 0.4, 2);
  else
    glOrtho(-1, 1, -1, 1, 2, 2);

  glVertexPointer(3, GL_DOUBLE, 0, obj.vertices_arr);
  glEnableClientState(GL_VERTEX_ARRAY);
  glLineWidth(width);
  glColor3d(lines_r, lines_g, lines_b);
  if (stipple)
    glLineStipple(1, 0x00FF);
  else
    glLineStipple(1, 0xFFFF);
  glEnable(GL_LINE_STIPPLE);
  glDrawElements(GL_LINES, obj.polygonals_count * 16, GL_UNSIGNED_INT,
                 obj.polygonals_arr);
  glDisableClientState(GL_VERTEX_ARRAY);

  if (points_mode > 0) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3d(points_r, points_g, points_b);
    glPointSize(size_points);
    if (points_mode == 2) {
      glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, obj.vertices_count);
      glDisable(GL_POINT_SMOOTH);
    } else
      glDrawArrays(GL_POINTS, 0, obj.vertices_count);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}
