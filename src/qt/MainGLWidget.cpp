#include <QMessageBox>
#include <QApplication>
#include <QDateTime>
#include <iostream>
#include <stdexcept>
#include <QOpenGLExtraFunctions>
#include <QResizeEvent>
#include <ui_MainWindow.h>
#include "MainGLWidget.hpp"



void MainGLWidget::initializeGL()
{
    // Set up the rendering context, load shaders and other resources, etc.:
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // ...
}

void MainGLWidget::resizeGL(int w, int h)
{
    QOpenGLWidget::resize(w,h);
    // Update projection matrix and other size related settings:
    // m_projection.setToIdentity();
    // m_projection.perspective(45.0f, w / float(h), 0.01f, 100.0f);
    // ...
}


void MainGLWidget::paintGL()
{
    // Draw the scene:
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT);
    // ...
}
