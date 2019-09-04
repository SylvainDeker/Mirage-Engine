#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "spheres/calcul.h"

#include <QMessageBox>
#include <QVBoxLayout>

#include <iostream>
#include <sstream>
#include <iomanip>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);

    openglWidget = new MyOpenGLWidget(this);
    openglWidget->resize(openglWidget->sizeHint());
    openglWidget->setFocus();

    setCentralWidget(openglWidget);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_action_Version_OpenGL_triggered() {
    std::stringstream message;
    message << "Qt version     : " << qVersion() << std::endl;
    message << "Renderer       : " << glGetString(GL_RENDERER) << std::endl;
    message << "Vendor         : " << glGetString(GL_VENDOR) << std::endl;
    message << "Version        : " << glGetString(GL_VERSION) << std::endl;
    message << "GLSL Version   : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    QMessageBox::information(this, "OpenGL Information", message.str().c_str());
}

void MainWindow::on_actionHello_clear_triggered() {
    openglWidget->activatedemo(0);
}

void MainWindow::on_actionHello_triangle_triggered() {
    openglWidget->activatedemo(1);
}

void MainWindow::on_actionHello_camera_triggered() {
    openglWidget->activatedemo(2);
}

void MainWindow::on_actionUV_spheres_triggered() {
    openglWidget->activatedemo(3);
}

void MainWindow::on_actionICO_spheres_triggered() {
    openglWidget->activatedemo(4);
}

void MainWindow::on_actionDiffuse_light_triggered() {
    openglWidget->activatedemo(5);
}

void MainWindow::on_actionApprox_err_triggered() {
    openglWidget->activatedemo(6);
}

void MainWindow::on_actionCalcul_triggered() {
    size_t max = 24;
    calculuvsphere(max);
    calculicosphere(max);
}
