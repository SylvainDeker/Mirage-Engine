#include "bspline.hpp"
#include "../glm/glm.hpp"
#include <vector>





BSpline::BSpline(){
  float dist = 1.f;

  for (size_t i = 0; i < 10; i++) {
    _controlPoints.push_back(glm::vec3( float(i)*dist , 1.f, 1.f ));
  }


}


const std::vector<glm::vec3> & BSpline::getControlPoints() const {
  return _controlPoints;
}
