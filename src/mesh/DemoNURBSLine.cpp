#include "DemoNURBSLine.hpp"
#include "../nurbs/NURBS.hpp"
#include "NURBSLine.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "../light/Light.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"

DemoNURBSLine::DemoNURBSLine(const std::map<std::string,Shader*> & shaders):DeprecatedMesh(shaders),
  _controlPoints(std::vector<glm::vec3>()),
  _meshLine(NURBSLine(shaders,_displayPoints)),
  _meshControlPoints(ControlPoints(shaders,_controlPoints)),
  _nurbs(NURBS(_controlPoints)) {

  float tmp = 0.1f;
  float zero = 0.0f;

  float dec =0.1f;

  _controlPoints.push_back(glm::vec3(zero,  zero, dec));  _weight.push_back(1.0);
  _controlPoints.push_back(glm::vec3(tmp, tmp, dec));  _weight.push_back(1.0);
  _controlPoints.push_back(glm::vec3(tmp*2,  zero, dec)); _weight.push_back(0.1);
  _controlPoints.push_back(glm::vec3(tmp*3,  tmp, dec));  _weight.push_back(1.0);
  _controlPoints.push_back(glm::vec3(tmp*4,  zero, dec));  _weight.push_back(1.0);
  _controlPoints.push_back(glm::vec3(tmp*5,  tmp, dec));  _weight.push_back(1.0);



}


DemoNURBSLine::~DemoNURBSLine(){

}


void DemoNURBSLine::initializeGeometry(){
  _nurbs.setOrderK(3);
  _nurbs.setModalVector();
  _nurbs.setWeightVector(_weight);
  _nurbs.getDisplayPoints(_displayPoints,100); // 100 discret points to display



  _meshLine.initializeGeometry();
  _meshControlPoints.initializeGeometry();
}


void DemoNURBSLine::draw(const DeprecatedDrawParameter & para){

  _meshLine.draw(para);
  _meshControlPoints.draw(para);

}
