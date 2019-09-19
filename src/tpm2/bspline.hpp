#ifndef BSPLINE_H_
#define BSPLINE_H_
#include <vector>

#include "../glm/glm.hpp"



class BSpline{
public:
  BSpline();

  const std::vector<glm::vec3> & getControlPoints() const ;

private:


std::vector<glm::vec3> _controlPoints;
std::vector<float> _modalVector;


};


















#endif // BSPLINE_H_
