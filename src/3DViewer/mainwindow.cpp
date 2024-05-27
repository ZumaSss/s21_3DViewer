#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setFixedSize(1240, 840);

  settings = new QSettings("harmunda", "3DViewer", this);
  loadSettings();

  if (ui->widget->mode)
    ui->radioButton_frustum->setChecked(true);
  else
    ui->radioButton_ortho->setChecked(true);

  if (ui->widget->stipple)
    ui->radioButton_lines_dotted->setChecked(true);
  else
    ui->radioButton_lines_solid->setChecked(true);

  if (ui->widget->points_mode == 0)
    ui->radioButton_points_null->setChecked(true);
  else if (ui->widget->points_mode == 1)
    ui->radioButton_points_square->setChecked(true);
  else
    ui->radioButton_points_circle->setChecked(true);

  connect(ui->pushButton_open_file, SIGNAL(clicked()), this,
          SLOT(on_click_read_file()));
  connect(ui->pushButton_move_x, SIGNAL(clicked()), this,
          SLOT(on_click_move_x()));
  connect(ui->pushButton_move_y, SIGNAL(clicked()), this,
          SLOT(on_click_move_y()));
  connect(ui->pushButton_move_z, SIGNAL(clicked()), this,
          SLOT(on_click_move_z()));
  connect(ui->pushButton_rotate_x, SIGNAL(clicked()), this,
          SLOT(on_click_rotate_x()));
  connect(ui->pushButton_rotate_y, SIGNAL(clicked()), this,
          SLOT(on_click_rotate_y()));
  connect(ui->pushButton_rotate_z, SIGNAL(clicked()), this,
          SLOT(on_click_rotate_z()));
  connect(ui->pushButton_scale, SIGNAL(clicked()), this,
          SLOT(on_click_model_scale()));

  connect(ui->widget, SIGNAL(send_filename(QString)), this,
          SLOT(get_filename(QString)));
  connect(ui->widget, SIGNAL(send_info_obj(model_data)), this,
          SLOT(get_info_obj(model_data)));
}

MainWindow::~MainWindow() {
  saveSettings();
  delete ui;
}

void MainWindow::saveSettings() {
  QMessageBox::StandardButton reply;
  reply = QMessageBox::question(
      this, "Выход из приложения",
      "Вы собираетесь выйти из программы, сохранить настройки?",
      QMessageBox::Yes | QMessageBox::No);
  if (reply == QMessageBox::Yes) {
    settings->setValue("mode", ui->widget->mode);
    settings->setValue("stipple", ui->widget->stipple);
    settings->setValue("points_mode", ui->widget->points_mode);

    settings->setValue("bg_r", ui->widget->bg_r);
    settings->setValue("bg_g", ui->widget->bg_g);
    settings->setValue("bg_b", ui->widget->bg_b);

    settings->setValue("lines_r", ui->widget->lines_r);
    settings->setValue("lines_g", ui->widget->lines_g);
    settings->setValue("lines_b", ui->widget->lines_b);

    settings->setValue("points_r", ui->widget->points_r);
    settings->setValue("points_g", ui->widget->points_g);
    settings->setValue("points_b", ui->widget->points_b);

    settings->setValue("width", ui->widget->width);
    settings->setValue("size_points", ui->widget->size_points);
  }
}

void MainWindow::loadSettings() {
  ui->widget->set_mode(settings->value("mode", false).toBool());
  ui->widget->set_stipple(settings->value("stipple", false).toBool());
  ui->widget->set_points_mode(settings->value("points_mode", 0).toInt());

  QColor *color = new QColor();
  color->setRgbF(settings->value("bg_r", 0).toDouble(),
                 settings->value("bg_g", 0).toDouble(),
                 settings->value("bg_b", 0).toDouble());
  ui->widget->set_bg_color(*color);

  color->setRgbF(settings->value("lines_r", 1).toDouble(),
                 settings->value("lines_g", 1).toDouble(),
                 settings->value("lines_b", 1).toDouble());
  ui->widget->set_lines_color(*color);

  color->setRgbF(settings->value("points_r", 1).toDouble(),
                 settings->value("points_g", 1).toDouble(),
                 settings->value("points_b", 1).toDouble());
  ui->widget->set_points_color(*color);

  ui->widget->load_width(settings->value("width", 1).toInt());
  ui->widget->load_size_points(settings->value("size_points", 1).toInt());

  delete color;
}

void MainWindow::on_click_read_file() { ui->widget->read_file(); }

void MainWindow::get_filename(QString file_name) {
  ui->lineEdit_Filename->setText(file_name);
  ui->plainTextEdit_info_file->setPlainText(
      "Название файла: " + QString(file_name.split("/").last()) + "\n");
}

void MainWindow::get_info_obj(model_data obj) {
  ui->plainTextEdit_info_file->setPlainText(
      ui->plainTextEdit_info_file->toPlainText() +
      "Количество вершин: " + QString::number(obj.vertices_count) +
      "\nКоличество ребер: " + QString::number(obj.polygonals_count));
}

void MainWindow::on_click_move_x() {
  ui->widget->move_x(ui->lineEdit_move->text().toDouble());
}

void MainWindow::on_click_move_y() {
  ui->widget->move_y(ui->lineEdit_move->text().toDouble());
}

void MainWindow::on_click_move_z() {
  ui->widget->move_z(ui->lineEdit_move->text().toDouble());
}

void MainWindow::on_click_rotate_x() {
  ui->widget->rotate_x(ui->lineEdit_rotate->text().toDouble());
}

void MainWindow::on_click_rotate_y() {
  ui->widget->rotate_y(ui->lineEdit_rotate->text().toDouble());
}

void MainWindow::on_click_rotate_z() {
  ui->widget->rotate_z(ui->lineEdit_rotate->text().toDouble());
}

void MainWindow::on_click_model_scale() {
  ui->widget->model_scale(ui->lineEdit_scale->text().toDouble());
}

void MainWindow::on_radioButton_ortho_clicked(bool checked) {
  if (checked) ui->widget->set_mode(false);
}

void MainWindow::on_radioButton_frustum_clicked(bool checked) {
  if (checked) ui->widget->set_mode(true);
}

void MainWindow::on_pushButton_set_color_clicked() {
  QColor color = QColorDialog::getColor(QColor(0, 0, 0));
  if (color.isValid()) ui->widget->set_bg_color(color);
}

void MainWindow::on_pushButton_set_lines_color_clicked() {
  QColor color = QColorDialog::getColor(QColor(1, 1, 1));
  if (color.isValid()) ui->widget->set_lines_color(color);
}

void MainWindow::on_radioButton_lines_solid_clicked(bool checked) {
  if (checked) ui->widget->set_stipple(false);
}

void MainWindow::on_radioButton_lines_dotted_clicked(bool checked) {
  if (checked) ui->widget->set_stipple(true);
}

void MainWindow::on_pushButton_width_lines_less_clicked() {
  ui->widget->set_width(false);
}

void MainWindow::on_pushButton_width_lines_more_clicked() {
  ui->widget->set_width(true);
}

void MainWindow::on_pushButton_set_points_color_clicked() {
  QColor color = QColorDialog::getColor(QColor(1, 1, 1));
  if (color.isValid()) ui->widget->set_points_color(color);
}

void MainWindow::on_pushButton_width_points_less_clicked() {
  ui->widget->set_size_points(false);
}

void MainWindow::on_pushButton_width_points_more_clicked() {
  ui->widget->set_size_points(true);
}

void MainWindow::on_radioButton_points_null_clicked(bool checked) {
  if (checked) ui->widget->set_points_mode(0);
}

void MainWindow::on_radioButton_points_circle_clicked(bool checked) {
  if (checked) ui->widget->set_points_mode(2);
}

void MainWindow::on_radioButton_points_square_clicked(bool checked) {
  if (checked) ui->widget->set_points_mode(1);
}

void MainWindow::on_pushButton_default_settings_clicked() {
  ui->radioButton_ortho->setChecked(true);
  ui->radioButton_lines_solid->setChecked(true);
  ui->radioButton_points_null->setChecked(true);

  ui->widget->set_mode(false);
  ui->widget->set_stipple(false);
  ui->widget->set_points_mode(0);

  QColor *color = new QColor();
  color->setRgbF(0, 0, 0);
  ui->widget->set_bg_color(*color);

  color->setRgbF(1, 1, 1);
  ui->widget->set_lines_color(*color);

  color->setRgbF(1, 1, 1);
  ui->widget->set_points_color(*color);

  ui->widget->load_width(1);
  ui->widget->load_size_points(1);

  delete color;
}

void MainWindow::on_pushButton_save_path_clicked() {
  QString dir = QFileDialog::getExistingDirectory(
      this, tr("Choose a directory..."), "../../",
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!dir.isEmpty()) ui->lineEdit_save_path->setText(dir);
}

void MainWindow::on_pushButton_jpeg_clicked() {
  if (!ui->lineEdit_save_path->text().isEmpty()) {
    ui->widget->grab().save(ui->lineEdit_save_path->text() +
                            "/screenshot_3DViewer_" +
                            QString::number(++image_id) + ".jpeg");
  }
}

void MainWindow::on_pushButton_bmp_clicked() {
  if (!ui->lineEdit_save_path->text().isEmpty()) {
    ui->widget->grab().save(ui->lineEdit_save_path->text() +
                            "/screenshot_3DViewer_" +
                            QString::number(++image_id) + ".bmp");
  }
}

void MainWindow::on_pushButton_gif_clicked() {
  miliseconds = 0;
  frame = new QImage();
  gif = new QGifImage();
  time = new QTimer();

  if (!ui->lineEdit_save_path->text().isEmpty() && !recording) {
    recording = true;
    connect(time, SIGNAL(timeout()), this, SLOT(make_gif()));
    time->start(100);
    ui->pushButton_gif->setText("Запись...");
  }
}

void MainWindow::make_gif() {
  *frame = ui->widget->grabFramebuffer();
  *frame = frame->scaled(640, 480);
  gif->addFrame(*frame, 100);
  miliseconds += 100;
  if (miliseconds >= 5000) {
    time->stop();
    gif->save(ui->lineEdit_save_path->text() + "/gif_3DViewer_" +
              QString::number(++image_id) + ".gif");
    recording = false;
    ui->pushButton_gif->setText("GIF");
  }
}
