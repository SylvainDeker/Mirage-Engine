#include "Mainwindow.hpp"

#include "ui_Mainwindow.h"


#include <QMessageBox>
#include <QVBoxLayout>

#include <iostream>
#include <sstream>
#include <iomanip>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    QSurfaceFormat format;
    format.setVersion(4, 1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);

    QSurfaceFormat::setDefaultFormat(format);

    ui->setupUi(this);

    openglWidget = new OpenGLWidget(this);
    openglWidget->resize(openglWidget->sizeHint());
    openglWidget->setFocus();

    setCentralWidget(openglWidget);
    // QTimer *timer = new QTimer(this);
    // connect(timer, &QTimer::timeout, this,&MainWindow::timer_out );
    // timer->start(30);
    // openglWidget->update();
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

void MainWindow::timer_out(){
  openglWidget->update();
}
