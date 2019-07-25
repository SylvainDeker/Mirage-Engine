#include <QMessageBox>
#include <QApplication>
#include <QDateTime>
#include <iostream>
#include <stdexcept>
#include <QOpenGLExtraFunctions>
#include <QResizeEvent>
#include <ui_MainWindow.h>
#include "MainGLWidget.hpp"

const std::string vertex_shader = "#version 330 core\n\
layout (location = 0) in vec3 aPos;\n\
void main()\n\
{ \n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n\
}";

const std::string fragment_shader = "#version 330 core\
out vec4 FragColor;\
\
void main()\
{\
    FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\
}";

void MainGLWidget::initializeGL()
{
  int  success;
  char infoLog[512];
    // Set up the rendering context, load shaders and other resources, etc.:
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    float vertices[] = {
      -0.5f, -0.5f, 0.0f,
       0.5f, -0.5f, 0.0f,
       0.0f,  0.5f, 0.0f
    };

    unsigned int VBO;
    f->glGenBuffers(1,&VBO); // VBO is to manage the memeory

    f->glBindBuffer(GL_ARRAY_BUFFER,VBO); // specify what kind of buffer is

    f->glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = f->glCreateShader(GL_VERTEX_SHADER);

    const char *vertex_shader_c = vertex_shader.c_str();
    f->glShaderSource(vertexShader, 1,&vertex_shader_c , NULL);


    f->glCompileShader(vertexShader);
    f->glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        f->glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        exit(-1);
    }


    unsigned int fragmentShader;
    fragmentShader = f->glCreateShader( GL_FRAGMENT_SHADER );
    const char *fragment_shader_c = fragment_shader.c_str();
    f->glShaderSource(fragmentShader, 1, &fragment_shader_c, NULL);
    f->glCompileShader(fragmentShader);


    unsigned int shaderProgram;
    shaderProgram = f->glCreateProgram();

    f->glAttachShader(shaderProgram, vertexShader);
    f->glAttachShader(shaderProgram, fragmentShader);
    f->glLinkProgram(shaderProgram);


    f->glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        f->glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "PROGRAM\n" << infoLog << std::endl;
    }

    f->glUseProgram(shaderProgram);

    f->glDeleteShader(vertexShader);
    f->glDeleteShader(fragmentShader);


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
