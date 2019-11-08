#include "DemoBSplineSurface.hpp"
#include "../bspline/Bspline.hpp"
#include "BSplineLine.hpp"
#include "BSplineSurface.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "../light/Light.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"

DemoBSplineSurface::DemoBSplineSurface(const std::vector<Shader*> & shaders):DeprecatedMesh(shaders),
  _controlPoints(std::vector<glm::vec3>()),
  _meshSurface(BSplineSurface(shaders,_displayPoints)),
  _meshControlPoints(ControlPoints(shaders,_controlPoints)),
  _bspline2D(BSpline2D(_controlPoints)){

  float tmp = 0.1f;
  float dec = 0.1f;
  float decm = 0.5f;
  _meshSurface.setDimXY(100,100);
  _bspline2D.setNX(6);
  _bspline2D.setNY(6);
  for (int i = 0; i <= _bspline2D.getNX(); i++) {
    for (int j = 0; j <= _bspline2D.getNY(); j++) {
      _controlPoints.push_back(glm::vec3(float(i)*tmp,float(j)*tmp, decm+dec*(glm::cos(float(i))+glm::sin(float(j))) ));
    }
  }

}


DemoBSplineSurface::~DemoBSplineSurface(){

}


void DemoBSplineSurface::initializeGeometry(){
  _bspline2D.setOrderKX(3);
  _bspline2D.setOrderKY(3);


  _bspline2D.setModalVectors();
  _bspline2D.getDisplayPoints(_displayPoints,100,100);



  _meshSurface.initializeGeometry();
  _meshControlPoints.initializeGeometry();
}



void DemoBSplineSurface::draw(const DeprecatedDrawParameter & para){

  _meshSurface.draw(para);
  _meshControlPoints.draw(para);

}
