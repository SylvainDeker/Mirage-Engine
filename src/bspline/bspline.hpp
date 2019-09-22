#ifndef BSPLINE_H_
#define BSPLINE_H_
#include <vector>

#include "../glm/glm.hpp"



class BSpline{
public:
  BSpline(
         std::vector<glm::vec3>& controlPoints,
         std::vector<float>& _modalVector);

void setOrderK(int k);
int getOrderK() const ;
int getN() const ;

private:


std::vector<glm::vec3> &_controlPoints;
std::vector<float> &_modalVector;
int _order_k;


};


















#endif // BSPLINE_H_
