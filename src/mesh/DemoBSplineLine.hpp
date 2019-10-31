#ifndef DEMOBSPLINE_H_
#define DEMOBSPLINE_H_
#include "../bspline/Bspline.hpp"
#include "../openGL/Shader.hpp"
#include "BSplineLine.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"


class DemoBSplineLine {

public:
  DemoBSplineLine();
  ~DemoBSplineLine ();
  void initializeGeometry();
  void draw(const std::vector<Shader*> & shader,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection);

private:
  std::vector<glm::vec3> _controlPoints;
  std::vector<glm::vec3> _displayPoints;
  BSplineLine _meshLine;
  ControlPoints _meshControlPoints;
  BSpline _bspline;



};

#endif // DEMOBSPLINE_H_
