#ifndef DEMOBSPLINESURFACE_H_
#define DEMOBSPLINESURFACE_H_
#include "../bspline/bspline2D.hpp"
#include "bSplineLine.h"
#include "bSplineSurface.h"
#include "controlPoints.h"
#include <vector>
#include "glm/glm.hpp"



class DemoBSplineSurface {

public:
  DemoBSplineSurface();
  ~DemoBSplineSurface ();
  void initializeGeometry();
  void draw(const std::vector<ProgramGL> & progGL,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection);


private:
  std::vector<glm::vec3> _controlPoints;
  std::vector<glm::vec3> _displayPoints;

  BSplineSurface _meshSurface;
  ControlPoints _meshControlPoints;
  BSpline2D _bspline2D;



};

#endif // DEMOBSPLINESURFACE_H_
