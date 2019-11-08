#include "Mainscene.hpp"
#include <iostream>
#include <QTime>
#include "../mesh/DemoBSplineLine.hpp"
#include "../mesh/DemoBSplineSurface.hpp"
#include "../mesh/Textu.hpp"
#include "../mesh/Cube.hpp"
#include "../mesh/Mesh.hpp"
#include "../light/Light.hpp"
#include "opengl_stuff.h"
#include "DrawParameter.hpp"
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/


#define deg2rad(x) float(M_PI)*(x)/180.f



MainScene::MainScene(int width, int height) : _width(width), _height(height),
      _drawfill(true),
      _meshes(std::vector<Mesh*>()),
      _shaders(std::vector<Shader*>()),
      _lights(std::vector<Light*>()),
      _activecamera(0),
      _camera(nullptr)



          {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    _meshes.push_back(new DemoBSplineLine(_shaders));
    _meshes.push_back(new DemoBSplineSurface(_shaders));
    _meshes.push_back(new Textu(_shaders));
    _meshes.push_back(new Cube(_shaders));
    _meshes.push_back(new Cube(_shaders));


    for (size_t i = 0; i < _meshes.size(); i++) {
      _meshes[i]->initializeGeometry();
    }

    _shaders.push_back(new Shader());
    _shaders.at(0)->loadfile("../shader/normal_VertexShader.glsl","../shader/normal_FragmentShader.glsl");

    _shaders.push_back(new Shader());
    _shaders.at(1)->loadfile("../shader/normal_VertexShader.glsl","../shader/normal_FragmentShader.glsl");

    _shaders.push_back(new Shader());
    _shaders.at(2)->loadfile("../shader/textu_VertexShader.glsl","../shader/textu_FragmentShader.glsl");

    _shaders.push_back(new Shader());
    _shaders.at(3)->loadfile("../shader/rand_VertexShader.glsl","../shader/rand_FragmentShader.glsl");

    _shaders.push_back(new Shader());
    _shaders.at(4)->loadfile("../shader/light_VertexShader.glsl","../shader/light_FragmentShader.glsl");

    _shaders.push_back(new Shader());
    _shaders.at(5)->loadfile("../shader/light_VertexShader.glsl","../shader/material_FragmentShader.glsl");


    _lights.push_back(new Light(glm::vec3(0.2f,1.f,1.f),glm::vec3(1.f,0.f,0.0f) ));



    _cameraselector.push_back( []()->Camera*{return new EulerCamera(glm::vec3(0.f, 0.f, 1.f));} );
    _cameraselector.push_back( []()->Camera*{return new TrackballCamera(glm::vec3(0.f, 0.f, 1.f),glm::vec3(0.f, 1.f, 0.f),glm::vec3(0.f, 0.f, 0.f));} );

    _camera.reset(_cameraselector[_activecamera]());

    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);

}

MainScene::~MainScene() {
    for (size_t i = 0; i < _meshes.size(); i++) {
      delete _meshes[i];
    }
    for (size_t i = 0; i < _shaders.size(); i++) {
      delete _shaders[i];
    }

}

void MainScene::resize(int width, int height){
  _width = width;
  _height = height;
  _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
  _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

void MainScene::draw() {

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  if (_drawfill)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  else
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    _view = _camera->viewmatrix();


    static size_t movvv= 0;
    glm::mat4 turn_model = glm::translate(_model,glm::vec3(0.f,0.f,0.5f));
    turn_model = glm::rotate(turn_model, glm::radians(float(movvv)) , glm::vec3(0.0f, 1.0f, 0.0f));



    for (Light *light : _lights) {

        _meshes.at(0)->draw(DrawParameter(_model,_view,_projection,light)); // DemoBSplineLine());

        _meshes.at(1)->draw(DrawParameter(_model,_view,_projection,light)); //DemoBSplineSurface());

        _meshes.at(2)->draw(DrawParameter(
                        glm::translate(_model,glm::vec3(0.f,-0.5f,0.0f)),
                        _view,
                        _projection,
                        light)
                      ); //Textu());

        _meshes.at(3)->draw(DrawParameter(
                        glm::scale(turn_model,glm::vec3(0.2f)),
                        _view,
                        _projection,
                        light)
                      ); // Cube());

        _meshes.at(4)->draw(DrawParameter(
                        glm::scale(glm::translate(_model,light->getPosition()),
                        glm::vec3(0.05f)),
                        _view,_projection,
                        light)
                      ); // Cube());

    }
    movvv+=3;
    if(movvv > 360)movvv = 0;
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

void MainScene::toggledrawmode() {
    _drawfill = !_drawfill;
}
