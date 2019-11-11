#include "DemoNURBSSurface.hpp"
#include "../nurbs/NURBS.hpp"
#include "NURBSLine.hpp"
#include "NURBSSurface.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "../light/Light.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"

// float abs(float a){ return a>0.f?a:-a;}

DemoNURBSSurface::DemoNURBSSurface(const std::map<std::string,Shader*> & shaders):DeprecatedMesh(shaders),
  _controlPoints(std::vector<glm::vec3>()),
  _meshSurface(NURBSSurface(shaders,_displayPoints)),
  _meshControlPoints(ControlPoints(shaders,_controlPoints)),
  _nurbs2D(NURBS2D(_controlPoints)){

  float tmp = 0.3f;
  float dec = 10.f;
  float decm = 0.3f;
  _meshSurface.setDimXY(100,100);
  _nurbs2D.setNX(10);
  _nurbs2D.setNY(10);
  for (int i = 0; i <= _nurbs2D.getNX(); i++) {
    for (int j = 0; j <= _nurbs2D.getNY(); j++) {
      _controlPoints.push_back(glm::vec3(
        float(i)*tmp,
        float(j)*tmp,
         decm*(glm::sin(dec*float(i))+glm::sin(dec*float(j))) ));
      _coef.push_back( (i>3 && i<7 && j>3 && j<7 ) ? 0.01f : 10.0f );
    }
  }

}


DemoNURBSSurface::~DemoNURBSSurface(){

}


void DemoNURBSSurface::initializeGeometry(){
  _nurbs2D.setOrderKX(3);
  _nurbs2D.setOrderKY(3);


  _nurbs2D.setModalVectors();
  _nurbs2D.setWeightVector(_coef);
  _nurbs2D.getDisplayPoints(_displayPoints,100,100);



  _meshSurface.initializeGeometry();
  _meshControlPoints.initializeGeometry();
}



void DemoNURBSSurface::draw(const DeprecatedDrawParameter & para){

  _meshSurface.draw(para);
  _meshControlPoints.draw(para);

}
