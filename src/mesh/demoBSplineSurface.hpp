#ifndef DEMOBSPLINESURFACE_H_
#define DEMOBSPLINESURFACE_H_
#include "../bspline/bspline2D.hpp"
#include "bSplineLine.h"
#include "bSplineSurface.h"
#include "controlPoints.h"
#include <vector>
#include "glm/glm.hpp"
#include "../openGL/drawElement.hpp"


class DemoBSplineSurface {

public:
  DemoBSplineSurface();
  ~DemoBSplineSurface ();
  void initializeGeometry();
  void draw(DrawElement de);


private:
  std::vector<glm::vec3> _controlPoints;
  std::vector<glm::vec3> _displayPoints;

  BSplineSurface _meshSurface;
  ControlPoints _meshControlPoints;
  BSpline2D _bspline2D;



};

#endif // DEMOBSPLINESURFACE_H_
