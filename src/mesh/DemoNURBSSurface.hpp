#ifndef DEMOBSPLINESURFACE_H_
#define DEMOBSPLINESURFACE_H_
#include "../nurbs/NURBS2D.hpp"
#include "NURBSLine.hpp"
#include "NURBSSurface.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "DeprecatedMesh.hpp"
#include "../light/Light.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"


class DemoNURBSSurface : public DeprecatedMesh{

public:
  DemoNURBSSurface(const std::map<std::string,Shader*> & shaders);
  ~DemoNURBSSurface () override ;
  void initializeGeometry() override ;

  void draw(const DeprecatedDrawParameter & para) override ;


private:
  std::vector<glm::vec3> _controlPoints;
  std::vector<glm::vec3> _displayPoints;
  std::vector<float> _coef ;

  NURBSSurface _meshSurface;
  ControlPoints _meshControlPoints;
  NURBS2D _nurbs2D;



};

#endif // DEMOBSPLINESURFACE_H_
