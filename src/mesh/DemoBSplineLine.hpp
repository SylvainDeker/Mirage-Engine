#ifndef DEMOBSPLINE_H_
#define DEMOBSPLINE_H_
#include "../bspline/Bspline.hpp"
#include "../openGL/Shader.hpp"
#include "BSplineLine.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "Mesh.hpp"
#include "../light/Light.hpp"


class DemoBSplineLine : public Mesh {

public:
  DemoBSplineLine(const std::vector<Shader*> & shaders);
  ~DemoBSplineLine () override ;
  void initializeGeometry() override ;
  void draw(
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection,
            const Light * light) override ;

private:
  std::vector<glm::vec3> _controlPoints;
  std::vector<glm::vec3> _displayPoints;
  BSplineLine _meshLine;
  ControlPoints _meshControlPoints;
  BSpline _bspline;



};

#endif // DEMOBSPLINE_H_
