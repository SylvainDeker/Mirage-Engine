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
  _meshControlPoints(ControlPoints()),
  _bspline(BSpline(_controlPoints,_modalVector)){


}
