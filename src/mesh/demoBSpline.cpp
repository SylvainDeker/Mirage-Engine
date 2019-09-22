#include "demoBSpline.hpp"
#include "../bspline/bspline.hpp"
#include "bSplineLine.h"
#include "controlPoints.h"
#include <vector>
#include "glm/glm.hpp"

DemoBSpline::DemoBSpline():
  _controlPoints(std::vector<glm::vec3>()),
  _modalVector(std::vector<float>()),
  _meshLine(BSplineLine()),
  _meshControlPoints(ControlPoints(_controlPoints)),
  _bspline(BSpline(_controlPoints,_modalVector)){

  float tmp = 0.1f;
  float dec =0.2f;

  _controlPoints.push_back(glm::vec3(tmp,  tmp, dec));  // Top Right
  _controlPoints.push_back(glm::vec3(tmp,  -tmp, dec));  // Bottom Right
  _controlPoints.push_back(glm::vec3(-tmp,  -tmp, dec)); // Bottom Left
  _controlPoints.push_back(glm::vec3(-tmp,  tmp, dec));  // Top Left

}


DemoBSpline::~DemoBSpline(){

}


void DemoBSpline::initializeGeometry(){
  _meshLine.initializeGeometry();
  _meshControlPoints.initializeGeometry();
}
void DemoBSpline::draw(){
  _meshLine.draw();
  _meshControlPoints.draw();
}
