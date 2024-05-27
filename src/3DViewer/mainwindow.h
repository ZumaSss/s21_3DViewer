#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gifimage/qgifimage.h>

#include <QColorDialog>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>

extern "C" {
#include <modules.h>
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void saveSettings();
  void loadSettings();

 private slots:
  void on_click_read_file();
  void get_filename(QString);
  void get_info_obj(model_data);

  void on_click_move_x();
  void on_click_move_y();
  void on_click_move_z();
  void on_click_rotate_x();
  void on_click_rotate_y();
  void on_click_rotate_z();
  void on_click_model_scale();

  void on_radioButton_ortho_clicked(bool checked);
  void on_radioButton_frustum_clicked(bool checked);
  void on_pushButton_set_color_clicked();
  void on_pushButton_set_lines_color_clicked();
  void on_radioButton_lines_solid_clicked(bool checked);
  void on_radioButton_lines_dotted_clicked(bool checked);
  void on_pushButton_width_lines_less_clicked();
  void on_pushButton_width_lines_more_clicked();
  void on_pushButton_set_points_color_clicked();
  void on_pushButton_width_points_less_clicked();
  void on_pushButton_width_points_more_clicked();
  void on_radioButton_points_null_clicked(bool checked);
  void on_radioButton_points_circle_clicked(bool checked);
  void on_radioButton_points_square_clicked(bool checked);
  void on_pushButton_default_settings_clicked();

  void on_pushButton_save_path_clicked();
  void on_pushButton_jpeg_clicked();
  void on_pushButton_bmp_clicked();
  void on_pushButton_gif_clicked();
  void make_gif();

 private:
  Ui::MainWindow *ui;
  QSettings *settings;

  int image_id = 0;
  QGifImage *gif;
  QImage *frame;
  QTimer *time;
  int miliseconds;
  bool recording = false;
};
#endif  // MAINWINDOW_H
