#include "DemoBSplineLine.hpp"
#include "../bspline/Bspline.hpp"
#include "BSplineLine.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "../light/Light.hpp"

DemoBSplineLine::DemoBSplineLine(const std::vector<Shader*> & shaders):Mesh(shaders),
  _controlPoints(std::vector<glm::vec3>()),
  _meshLine(BSplineLine(shaders,_displayPoints)),
  _meshControlPoints(ControlPoints(shaders,_controlPoints)),
  _bspline(BSpline(_controlPoints)) {

  float tmp = 0.1f;
  float zero = 0.0f;

  float dec =0.0f;

  _controlPoints.push_back(glm::vec3(zero,  zero, dec));  // Top Right
  _controlPoints.push_back(glm::vec3(tmp, tmp, dec));  // Bottom Right
  _controlPoints.push_back(glm::vec3(tmp*2,  zero, dec)); // Bottom Left
  _controlPoints.push_back(glm::vec3(tmp*3,  tmp, dec));  // Top Left
  _controlPoints.push_back(glm::vec3(tmp*4,  zero, dec));  // Top Left
  _controlPoints.push_back(glm::vec3(tmp*5,  tmp, dec));  // Top Left


}


DemoBSplineLine::~DemoBSplineLine(){

}


void DemoBSplineLine::initializeGeometry(){
  _bspline.setOrderK(3);
  _bspline.setModalVector();
  _bspline.getDisplayPoints(_displayPoints,100); // 100 discret points to display



  _meshLine.initializeGeometry();
  _meshControlPoints.initializeGeometry();
}


void DemoBSplineLine::draw(
          const glm::mat4 & model,
          const glm::mat4 & view,
          const glm::mat4 & projection,
          const Light * light){

  _meshLine.draw(model,view,projection,light);
  _meshControlPoints.draw(model,view,projection,light);

}
