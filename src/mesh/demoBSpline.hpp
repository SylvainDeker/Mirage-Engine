#ifndef DEMOBSPLINE_H_
#define DEMOBSPLINE_H_
#include "../bspline/bspline.hpp"
#include "bSplineLine.h"
#include "controlPoints.h"
#include <vector>
#include "glm/glm.hpp"


class DemoBSpline {

public:
  DemoBSpline();
  ~DemoBSpline ();
  void initializeGeometry();
  void draw();


private:
  std::vector<glm::vec3> _controlPoints;
  std::vector<glm::vec3> _displayPoints;
  BSplineLine _meshLine;
  ControlPoints _meshControlPoints;
  BSpline _bspline;



};

#endif // DEMOBSPLINE_H_
