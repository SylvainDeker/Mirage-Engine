#include "openglmain.h"
#include <iostream>


OpenGLMain::OpenGLMain(int width, int height) : _width(width), _height(height), _drawfill(true) {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);
}

OpenGLMain::~OpenGLMain() {
}

void OpenGLMain::resize(int width, int height) {
   _width = width;
   _height = height;
}

void OpenGLMain::draw() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if (_drawfill)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void OpenGLMain::mouseclick(int , float , float ) {

}

void OpenGLMain::mousemove(float , float ) {

}

void OpenGLMain::keyboardmove(int , double ) {

}

bool OpenGLMain::keyboard(unsigned char ) {
    return false;
}

void OpenGLMain::toggledrawmode() {
    _drawfill = !_drawfill;
}
