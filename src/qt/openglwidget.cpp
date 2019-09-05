#include "openglwidget.h"

#include <QMessageBox>
#include <QApplication>
#include <QDateTime>

#include <iostream>
#include <stdexcept>

#include "../openGL/mainscene.h"



OpenGLWidget::OpenGLWidget(QWidget *parent) :QOpenGLWidget(parent)/*, QOpenGLFunctions_4_1_Core()*/, _openglDemo(nullptr), _lastime(0) {
    // add all demo constructors here

    _democonstructors = [](int width, int height)->OpenGLDemo*{
       return new MainScene(width, height);
    };
}

OpenGLWidget::~OpenGLWidget() {

}

QSize OpenGLWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize OpenGLWidget::sizeHint() const
{
    return QSize(512, 512);
}

void OpenGLWidget::cleanup() {
    _openglDemo.reset(nullptr);
}

void OpenGLWidget::initializeGL() {
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &OpenGLWidget::cleanup);

    if (!initializeOpenGLFunctions()) {
        QMessageBox::critical(this, "OpenGL initialization error", "OpenGLWidget::initializeGL() : Unable to initialize OpenGL functions");
        exit(1);
    }
    // Initialize OpenGL and all OpenGL dependent stuff below
    _openglDemo.reset(_democonstructors(width(), height()));
}

void OpenGLWidget::paintGL() {
    std::int64_t starttime = QDateTime::currentMSecsSinceEpoch();
    _openglDemo->draw();
    glFinish();
    std::int64_t endtime = QDateTime::currentMSecsSinceEpoch();
    _lastime = endtime-starttime;
}

void OpenGLWidget::resizeGL(int width, int height) {
    _openglDemo->resize(width, height);
}

void OpenGLWidget::mousePressEvent(QMouseEvent *event) {
    // buttons are 0(left), 1(right) to 2(middle)
    int b;
    Qt::MouseButton button=event->button();
    if (button & Qt::LeftButton) {
        if ((event->modifiers() & Qt::ControlModifier))
            b = 2;
        else
            b = 0;
    } else if (button & Qt::RightButton)
        b = 1;
    else if (button & Qt::MiddleButton)
        b = 2;
    else
        b=3;
    _openglDemo->mouseclick(b, event->x(), event->y());
    _lastime = QDateTime::currentMSecsSinceEpoch();
}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event) {
    _openglDemo->mousemove(event->x(), event->y());
    update();
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event) {
    switch(event->key()) {
        // Demo keys
        case Qt::Key_0:
        case Qt::Key_1:
        case Qt::Key_2:
        case Qt::Key_3:
        case Qt::Key_4:
        case Qt::Key_5:
        case Qt::Key_6:
        case Qt::Key_7:
        case Qt::Key_8:
        case Qt::Key_9:
            activatedemo(event->key()-Qt::Key_0);
        break;
        // Move keys
        case Qt::Key_Left:
        case Qt::Key_Up:
        case Qt::Key_Right:
        case Qt::Key_Down:
            _openglDemo->keyboardmove(event->key()-Qt::Key_Left, 1./100/*double(_lastime)/10.*/);
            update();
        break;
        // Wireframe key
        case Qt::Key_W:
            _openglDemo->toggledrawmode();
            update();
        break;
        // Other keys are transmitted to the scene
        default :
            if (_openglDemo->keyboard(event->text().toStdString()[0]))
                update();
        break;
    }
}

void OpenGLWidget::activatedemo(unsigned int numdemo) {
    (void) numdemo;
    std::cout << "Activating demo " << numdemo << " : ";
    makeCurrent();
    _openglDemo.reset(_democonstructors(width(), height()));
    doneCurrent();
    update();

}
