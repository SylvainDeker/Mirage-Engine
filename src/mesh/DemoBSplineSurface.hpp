#ifndef DEMOBSPLINESURFACE_H_
#define DEMOBSPLINESURFACE_H_
#include "../bspline/Bspline2D.hpp"
#include "BSplineLine.hpp"
#include "BSplineSurface.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "DeprecatedMesh.hpp"
#include "../light/Light.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"


class DemoBSplineSurface : public DeprecatedMesh{

public:
  DemoBSplineSurface(const std::map<std::string,Shader*> & shaders);
  ~DemoBSplineSurface () override ;
  void initializeGeometry() override ;

  void draw(const DeprecatedDrawParameter & para) override ;


private:
  std::vector<glm::vec3> _controlPoints;
  std::vector<glm::vec3> _displayPoints;

  BSplineSurface _meshSurface;
  ControlPoints _meshControlPoints;
  BSpline2D _bspline2D;



};

#endif // DEMOBSPLINESURFACE_H_
