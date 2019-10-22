#include "mainscene.h"
#include <iostream>
#include "mesh.h"
#include "../mesh/demoBSplineLine.hpp"
#include "../mesh/demoBSplineSurface.hpp"

/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/


#define deg2rad(x) float(M_PI)*(x)/180.f



MainScene::MainScene(int width, int height) : OpenGLMain(width, height),
      _progGL(std::vector<ProgramGL>()),
      _activecamera(0),
      _camera(nullptr),
      _demoBSplineLine(DemoBSplineLine()),
      _demoBSplineSurface(DemoBSplineSurface())



          {





    _demoBSplineLine.initializeGeometry();
    _demoBSplineSurface.initializeGeometry();

    _progGL.push_back(ProgramGL());

    _progGL[0].loadfile("../shader/normal_VertexShader.glsl","../shader/normal_FragmentShader.glsl");







    _cameraselector.push_back( []()->Camera*{return new EulerCamera(glm::vec3(0.f, 0.f, 1.f));} );
    _cameraselector.push_back( []()->Camera*{return new TrackballCamera(glm::vec3(0.f, 0.f, 1.f),glm::vec3(0.f, 1.f, 0.f),glm::vec3(0.f, 0.f, 0.f));} );

    _camera.reset(_cameraselector[_activecamera]());

    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

MainScene::~MainScene() {
    // glDeleteProgram(_program);
}

void MainScene::resize(int width, int height){
    OpenGLMain::resize(width, height);
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

void MainScene::draw() {
    OpenGLMain::draw();

    _view = _camera->viewmatrix();



    _demoBSplineLine.draw(_progGL,_model,_view,_projection);
    _demoBSplineSurface.draw(_progGL,_model,_view,_projection);

}

void MainScene::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    _camera->processmouseclick(_button, xpos, ypos);
}

void MainScene::mousemove(float xpos, float ypos) {
    _camera->processmousemovement(_button, xpos, ypos, true);
}

void MainScene::keyboardmove(int key, double time) {
    _camera->processkeyboard(Camera_Movement(key), time);
}

bool MainScene::keyboard(unsigned char k) {
    switch(k) {
        case 'p':
            _activecamera = (_activecamera+1)%2;
            _camera.reset(_cameraselector[_activecamera]());
            _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
            return true;
        default:
            return false;
    }
}
