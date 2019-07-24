#ifndef MainGLWidget_H
#define MainGLWidget_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>



class MainGLWidget : public QOpenGLWidget
{
public:
    MainGLWidget(QWidget *parent) : QOpenGLWidget(parent) { }

protected:
    void initializeGL() override ;

    void resizeGL(int w, int h) override ;

    void paintGL() override ;


};
#endif // MainGLWidget_H
