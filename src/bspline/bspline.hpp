#ifndef BSPLINE_H_
#define BSPLINE_H_
#include <vector>

#include "../glm/glm.hpp"



class BSpline{
public:
  BSpline(
         std::vector<glm::vec3>& controlPoints);

  void setOrderK(int k);
  int getOrderK() const ;
  int getN() const ;
  void setModalVector();
  void getDisplayPoints(std::vector<glm::vec3> & vertices,size_t points) const ;
  glm::vec3 polynom(float u) const ;
  void checkmemory();
private:
  float bsplineFunction(float u,int k,int i) const ;

  std::vector<glm::vec3> &_controlPoints;
  std::vector<float> _modalVector;
  int _order_k;


};


















#endif // BSPLINE_H_
