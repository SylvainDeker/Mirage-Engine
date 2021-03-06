#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Openglwidget.hpp"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_Version_OpenGL_triggered();
    void timer_out();

private:
    Ui::MainWindow *ui;
    OpenGLWidget *openglWidget;
};

#endif // MAINWINDOW_H
