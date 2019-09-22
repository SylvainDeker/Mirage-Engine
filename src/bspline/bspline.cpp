#include "bspline.hpp"
#include "../glm/glm.hpp"
#include <vector>





BSpline::BSpline(std::vector<glm::vec3>& controlPoints,
                std::vector<float>& modalVector):
  _controlPoints(controlPoints),
  _modalVector(modalVector),
  _order_k(1){


}


void BSpline::setOrderK(int k){
  _order_k = k;
}

int BSpline::getOrderK() const {
  return _order_k;
}

int BSpline::getN() const {
  return _controlPoints.size()- 1;
}
