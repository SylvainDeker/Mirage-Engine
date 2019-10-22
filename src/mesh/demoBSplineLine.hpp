#ifndef DEMOBSPLINE_H_
#define DEMOBSPLINE_H_
#include "../bspline/bspline.hpp"
#include "../openGL/programGL.hpp"
#include "bSplineLine.h"
#include "controlPoints.h"
#include <vector>
#include "glm/glm.hpp"


class DemoBSplineLine {

public:
  DemoBSplineLine();
  ~DemoBSplineLine ();
  void initializeGeometry();
  void draw(const std::vector<ProgramGL> & progGL,
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
