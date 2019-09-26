#ifndef BSPLINE2D_H_
#define BSPLINE2D_H_
#include <vector>

#include "../glm/glm.hpp"



class BSpline2D{
public:
  BSpline2D(
         std::vector<glm::vec3>& controlPoints);

  void setOrderKX(int k);
  void setOrderKY(int k);
  int getOrderKX() const ;
  int getOrderKY() const ;
  int getNX() const ;
  int getNY() const ;
  void setModalVectors();
  void getDisplayPoints(std::vector<glm::vec3> & vertices,size_t pointsX,size_t pointsY) const ;
  glm::vec3 polynom(float u,float v) const ;
  size_t getIdx(size_t x,size_t y) const ;
  void setNX(int n);
  void setNY(int n);


private:
  // float bsplineFunction(float u,float v,int kx,int ky,int i,int j) const ;
float bsplineFunction(float u,int k,int i,const std::vector<float> & modalVector) const ;


  std::vector<glm::vec3> &_controlPoints;
  std::vector<float> _modalVectorX;
  std::vector<float> _modalVectorY;
  int _order_kx;
  int _order_ky;
  int _nx;
  int _ny;


};


















#endif // BSPLINE2D_H_
