#include "demoBSplineSurface.hpp"
#include "../bspline/bspline.hpp"
#include "bSplineLine.h"
#include "bSplineSurface.h"
#include "controlPoints.h"
#include <vector>
#include "glm/glm.hpp"

DemoBSplineSurface::DemoBSplineSurface():
  _controlPoints(std::vector<glm::vec3>()),
  _meshSurface(BSplineSurface(_displayPoints)),
  _meshControlPoints(ControlPoints(_controlPoints)),
  _bspline(BSpline(_controlPoints)){

  float tmp = 0.1f;
  float dec = 0.1f;
  float decm = 0.5f;
  _meshSurface.setDimXY(30,40);
  for (size_t i = 0; i < _meshSurface.getDimX(); i++) {
    for (size_t j = 0; j < _meshSurface.getDimY(); j++) {
      _controlPoints.push_back(glm::vec3(float(i)*tmp,float(j)*tmp, decm+dec*(glm::cos(float(i))+glm::sin(float(j))) ));
    }
  }

}


DemoBSplineSurface::~DemoBSplineSurface(){

}


void DemoBSplineSurface::initializeGeometry(){
  // _bspline.setOrderK(3);
  // _bspline.setModalVector();
  // _bspline.getDisplayPoints(_displayPoints,100); // 10 discret point to display
  //
  //
  //
  _meshSurface.initializeGeometry();
  _meshControlPoints.initializeGeometry();
}


void DemoBSplineSurface::draw(){
  _meshSurface.draw();
  _meshControlPoints.draw();
}
