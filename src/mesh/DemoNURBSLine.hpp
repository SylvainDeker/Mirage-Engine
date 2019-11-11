#ifndef DEMOBSPLINE_H_
#define DEMOBSPLINE_H_
#include "../nurbs/NURBS.hpp"
#include "../openGL/Shader.hpp"
#include "NURBSLine.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "DeprecatedMesh.hpp"
#include "../light/Light.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"


class DemoNURBSLine : public DeprecatedMesh {

public:
  DemoNURBSLine(const std::map<std::string,Shader*> & shaders);
  ~DemoNURBSLine () override ;
  void initializeGeometry() override ;
  void draw(const DeprecatedDrawParameter & para) override ;

private:
  std::vector<glm::vec3> _controlPoints;
  std::vector<glm::vec3> _displayPoints;
  std::vector<float> _weight;
  NURBSLine _meshLine;
  ControlPoints _meshControlPoints;
  NURBS _nurbs;



};

#endif // DEMOBSPLINE_H_
