#include "bspline2D.hpp"
#include "../glm/glm.hpp"
#include <vector>
#include <assert.h>
#include <iostream>




BSpline2D::BSpline2D(std::vector<glm::vec3>& controlPoints):
  _controlPoints(controlPoints),
  _order_kx(1),
  _order_ky(1){

}


size_t BSpline2D::getIdx(size_t x,size_t y) const {

  size_t idx = x*(getNY()+1)+y;

  return idx;
}

void BSpline2D::setOrderKX(int k){
  assert(k>=1);
  _order_kx = k;
}

void BSpline2D::setOrderKY(int k){
  assert(k>=1);
  _order_ky = k;
}

int BSpline2D::getOrderKX() const {
  return _order_kx;
}
int BSpline2D::getOrderKY() const {
  return _order_ky;
}

int BSpline2D::getNX() const {
  return _nx;
}

int BSpline2D::getNY() const {
  return _ny;
}

void BSpline2D::setNX(int n){
  _nx = n;
}
void BSpline2D::setNY(int n){
  _ny = n;
}


void BSpline2D::setModalVectors(){
  assert(getOrderKX()>=1);
  assert(getOrderKY()>=1);
  assert(getNX()>=0);
  assert(getNY()>=0);
  size_t node_number_x = getOrderKX() + getNX()+1;
  _modalVectorX.clear();
  for (size_t i = 0; i < node_number_x; i++) {
    _modalVectorX.push_back(float(i));
  }
  size_t node_number_y = getOrderKY() + getNY()+1;
  _modalVectorY.clear();
  for (size_t i = 0; i < node_number_y; i++) {
    _modalVectorY.push_back(float(i));
  }
}

void BSpline2D::setModalVectors(const std::vector<float> & modalVectorX, const std::vector<float> & modalVectorY){
  assert(int(modalVectorX.size())==getNX()+1);
  assert(int(modalVectorY.size())==getNY()+1);
  _modalVectorX = modalVectorX;
  _modalVectorY = modalVectorY;
}



float BSpline2D::recFloraison(float u,int k,int i,const std::vector<float> & modalVector) const {
  assert(u>=0.f);
  assert(k>0);

  if(k==1){
    if( u >=modalVector[i]  && u < modalVector[i+1] ) return 1.f;
    else                    return 0.f;
  }
  else{
    return ((u-modalVector[i])/(modalVector[i+k-1] - modalVector[i])) * recFloraison(u,k-1,i,modalVector) + ((modalVector[i+k] - u)/(modalVector[i+k] - modalVector[i+1]))*recFloraison(u,k-1,i+1,modalVector);
  }
}


glm::vec3 BSpline2D::polynom(float u,float v) const {
  glm::vec3 acc=glm::vec3(0.f,0.f,0.f);
  for (int i = 0; i <= getNX() ; i++) {
    for (int j = 0; j <= getNY(); j++) {
      acc += recFloraison(u,getOrderKX(),i,_modalVectorX) * recFloraison(v,getOrderKY(),j,_modalVectorY) * _controlPoints[getIdx(i,j)];
    }
  }
  return acc;
}





void BSpline2D::getDisplayPoints(std::vector<glm::vec3> & vertices,size_t pointsX, size_t pointsY) const {
  assert(int(_modalVectorX.size())==getOrderKX()+getNX()+1);
  assert(int(_modalVectorY.size())==getOrderKY()+getNY()+1);
  float minX = _modalVectorX[getOrderKX()-1];
  float maxX = _modalVectorX[getNX()+1];
  float minY = _modalVectorY[getOrderKY()-1];
  float maxY = _modalVectorY[getNY()+1];
  float distX = maxX-minX;
  float distY = maxY-minY;
  float unitX = distX/float(pointsX);
  float unitY = distY/float(pointsY);
  glm::vec3 v;

  for (size_t i = 0; i < pointsX; i++) {
    for (size_t j = 0; j < pointsY; j++) {

      v = polynom(unitX*float(i)+minX,unitY*float(j)+minY);
      vertices.push_back(v);
    }
  }
}
