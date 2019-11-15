#include "Mainscene.hpp"
#include <iostream>
#include <QTime>
#include <map>
#include "../mesh/DemoNURBSLine.hpp"
#include "../mesh/DemoNURBSSurface.hpp"
#include "../mesh/Textu.hpp"
#include "../mesh/Cube.hpp"
#include "../mesh/DeprecatedMesh.hpp"
#include "../light/Light.hpp"
#include "../mesh/Model.hpp"
#include "../mesh/CubeMap.hpp"
#include "../mesh/IcoSphere.hpp"
#include "opengl_stuff.h"
#include "DeprecatedDrawParameter.hpp"
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/



MainScene::MainScene(int width, int height) : _width(width), _height(height),
      _drawfill(true),
      _meshes(std::vector<DeprecatedMesh*>()),
      _models(std::vector<Model*>()),
      _shaders(std::map<std::string,Shader*>()),
      _lights(std::vector<Light*>()),
      _activecamera(0),
      _camera(nullptr)



          {
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, width, height);

    _meshes.push_back(new DemoNURBSLine(_shaders));
    _meshes.push_back(new DemoNURBSSurface(_shaders));
    _meshes.push_back(new Textu(_shaders));
    _meshes.push_back(new Cube(_shaders));
    _meshes.push_back(new Cube(_shaders));
    _meshes.push_back(new Cube(_shaders));
    _meshes.push_back(new IcoSphere(_shaders,0));
    _meshes.push_back(new IcoSphere(_shaders,1));
    _meshes.push_back(new IcoSphere(_shaders,2));
    _meshes.push_back(new CubeMap(_shaders));

    _models.push_back(new Model("../model/Boat/boat.3ds"));
    _models.push_back(new Model("../model/Crysis/nanosuit.obj"));


    for (size_t i = 0; i < _meshes.size(); i++) {
      _meshes[i]->initializeGeometry();
    }

    _shaders.insert(std::pair<std::string,Shader*>("normal", new Shader()));
    _shaders.at("normal")->loadfile("../shader/normal_VertexShader.glsl","../shader/normal_FragmentShader.glsl");

    _shaders.insert(std::pair<std::string,Shader*>("normal2", new Shader()));
    _shaders.at("normal2")->loadfile("../shader/normal_VertexShader.glsl","../shader/normal_FragmentShader.glsl");

    _shaders.insert(std::pair<std::string,Shader*>("textu", new Shader()));
    _shaders.at("textu")->loadfile("../shader/textu_VertexShader.glsl","../shader/textu_FragmentShader.glsl");

    _shaders.insert(std::pair<std::string,Shader*>("rand", new Shader()));
    _shaders.at("rand")->loadfile("../shader/rand_VertexShader.glsl","../shader/rand_FragmentShader.glsl");

    _shaders.insert(std::pair<std::string,Shader*>("light", new Shader()));
    _shaders.at("light")->loadfile("../shader/light_VertexShader.glsl","../shader/light_FragmentShader.glsl");

    _shaders.insert(std::pair<std::string,Shader*>("l+m", new Shader()));
    _shaders.at("l+m")->loadfile("../shader/light_VertexShader.glsl","../shader/material_FragmentShader.glsl");

    _shaders.insert(std::pair<std::string,Shader*>("loader", new Shader()));
    _shaders.at("loader")->loadfile("../shader/loader_VertexShader.glsl","../shader/loader_FragmentShader.glsl");

    _shaders.insert(std::pair<std::string,Shader*>("cubemaps", new Shader()));
    _shaders.at("cubemaps")->loadfile("../shader/cubemaps_VertexShader.glsl","../shader/cubemaps_FragmentShader.glsl");

    _shaders.insert(std::pair<std::string,Shader*>("skybox", new Shader()));
    _shaders.at("skybox")->loadfile("../shader/skybox_VertexShader.glsl","../shader/skybox_FragmentShader.glsl");


    // _lights.push_back(new Light(glm::vec3(1.f,1.f,1.f),glm::vec3(0.5f,0.f,0.0f) ));
    _lights.push_back(new Light(glm::vec3(1.0f,1.f,1.f),glm::vec3(-0.5f,0.f,0.2f) ));



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
    for (std::map<std::string,Shader*>::iterator it= _shaders.begin(); it!=_shaders.end(); ++it){
      delete it->second;
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

  glDepthFunc(GL_LESS); // DepthBuff

  if (_drawfill)
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  else
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    _view = _camera->viewmatrix();


    static size_t movvv= 0;
    glm::mat4 turn_model = glm::translate(_model,glm::vec3(0.f,0.f,0.5f));
    turn_model = glm::rotate(turn_model, glm::radians(float(movvv)) , glm::vec3(0.0f, 1.0f, 0.0f));



    for (Light *light : _lights) {

        /////////// Basic Mesh
        _meshes.at(0)->draw(DeprecatedDrawParameter(
                      glm::translate(_model,glm::vec3(-1.f,-0.5f,0.0f)),
                      _camera.get(),
                      _projection,light
                    )); // DemoNURBSLine());

        _meshes.at(1)->draw(DeprecatedDrawParameter(
                      glm::translate(
                        glm::rotate(_model,
                          glm::radians(45.f),
                          glm::vec3(0.f,-1.f,0.f)
                        ),
                        glm::vec3(-1.1f,-1.5f,-3.0f)
                      ),
                      _camera.get(),
                      _projection,
                      light)); //DemoNURBSSurface());

        _meshes.at(2)->draw(DeprecatedDrawParameter(
                        glm::translate(_model,glm::vec3(0.f,-0.5f,0.0f)),
                        _camera.get(),
                        _projection,
                        light)
                      ); //Textu());

        _meshes.at(3)->draw(DeprecatedDrawParameter(
                        glm::scale(turn_model,glm::vec3(0.1f)),
                        _camera.get(),
                        _projection,
                        light)
                      ); // Cube());

        // _meshes.at(4)->draw(DeprecatedDrawParameter(
        //                 // glm::scale(glm::translate(_model,_lights[0]->getPosition()),glm::vec3(0.05f) ),
        //                 _model,
        //                 _camera.get(),
        //                 _projection,
        //                 light)
        //               ); // Cube());

        _meshes.at(5)->draw(DeprecatedDrawParameter(
                        glm::scale(glm::translate(_model,_lights[1]->getPosition()),glm::vec3(0.05f) ),
                        _camera.get(),
                        _projection,
                        light)
                      ); // Cube());

        _meshes.at(6)->draw(DeprecatedDrawParameter(
                        glm::translate(_model,glm::vec3(-0.50f, 0.8f, 0.0f)),
                        _camera.get(),
                        _projection,
                        light)
                      ); // IcoSphere());

        _meshes.at(7)->draw(DeprecatedDrawParameter(
                        glm::translate(_model,glm::vec3(-0.5f, 0.4f, 0.0f)),
                        _camera.get(),
                        _projection,
                        light)
                      ); // IcoSphere());

        _meshes.at(8)->draw(DeprecatedDrawParameter(
                        glm::translate(_model,glm::vec3(-0.50f, 0.0f, 0.0f)),
                        _camera.get(),
                        _projection,
                        light)
                      ); // IcoSphere());


        //////// Assimp mesh
        _models.at(0)->draw(DrawParameter(_shaders.at("loader"),
              glm::scale(
                glm::translate(
                  glm::rotate(_model,
                    glm::radians(90.f) , glm::vec3(-1.0f, 0.0f, 0.0f)
                  ),
                  glm::vec3(-1.0f,2.f,-1.0f)
                ),
                glm::vec3(0.10f)
              ),
              _camera.get(),
              _projection,
              light
      ));

      _models.at(1)->draw(DrawParameter(_shaders.at("loader"),
              glm::scale(
                glm::translate(
                  glm::rotate(_model,
                    glm::radians(1.f) , glm::vec3(1.0f, 0.0f, 0.0f)
                  ),
                  glm::vec3(0.0f,-1.f,-2.0f)
                ),
                glm::vec3(0.20f)
              ),
              _camera.get(),
              _projection,
              light
    ));


        // CubeMap TODO make a dedicated class
        _meshes.at(_meshes.size()-1)->draw(DeprecatedDrawParameter(_model, _camera.get(),_projection,light));

    }
    movvv+=1;
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
