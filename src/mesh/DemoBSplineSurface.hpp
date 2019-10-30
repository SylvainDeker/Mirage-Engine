#ifndef DEMOBSPLINESURFACE_H_
#define DEMOBSPLINESURFACE_H_
#include "../bspline/Bspline2D.hpp"
#include "BSplineLine.hpp"
#include "BSplineSurface.hpp"
#include "ControlPoints.hpp"
#include <vector>
#include "glm/glm.hpp"



class DemoBSplineSurface {

public:
  DemoBSplineSurface();
  ~DemoBSplineSurface ();
  void initializeGeometry();
  void draw(const std::vector<Shader> & shader,
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
