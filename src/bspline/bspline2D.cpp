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

// float BSpline2D::bsplineFunction(float u,float v,int kx,int ky,int i,int j) const {
//   assert(u>=0.f);
//   assert(v>=0.f);
//   assert(kx>0);
//   assert(ky>0);
//
//   // std::cout << u << ","<< v << ","<<kx<< ","<<ky<< ","<<i<< ","<<j<< '\n';
//
//   if(kx==1&&ky==1){
//     if( (u >=_modalVectorX[i]  && u < _modalVectorX[i+1]) && (v >=_modalVectorY[j]  && v < _modalVectorY[j+1]) ) return 1.f;
//     else                    return 0.f;
//   }
//   else if(kx==1){
//     return ((v-_modalVectorY[j])/(_modalVectorY[j+ky-1] - _modalVectorY[j])) * bsplineFunction(u,v,kx,ky-1,i,j)
//     + ((_modalVectorY[j+ky] - v)/(_modalVectorY[j+ky] - _modalVectorY[j+1])) * bsplineFunction(u,v,kx,ky-1,i+1,j);
//   }
//   else if(ky==1){
//     return ((u-_modalVectorX[i])/(_modalVectorX[i+kx-1] - _modalVectorX[i])) * bsplineFunction(u,v,kx-1,ky,i,j)
//     + ((_modalVectorX[i+kx] - u)/(_modalVectorX[i+kx] - _modalVectorX[i+1]))*bsplineFunction(u,v,kx-1,ky,i+1,j);
//
//   }
//   else{
//     assert(0);
//   }
//
//   // if(kx==1){
//   //   if( u >=_modalVectorX[i]  && u < _modalVectorX[i+1] ) return 1.f;
//   //   else                    return 0.f;
//   // }
//   // else{
//   //   return ((u-_modalVector[i])/(_modalVector[i+k-1] - _modalVector[i])) * bsplineFunction(u,k-1,i) + ((_modalVector[i+k] - u)/(_modalVector[i+k] - _modalVector[i+1]))*bsplineFunction(u,k-1,i+1);
//   // }
//
//   return 1.f;
// }


float BSpline2D::bsplineFunction(float u,int k,int i,const std::vector<float> & modalVector) const {
  assert(u>=0.f);
  assert(k>0);

  if(k==1){
    if( u >=modalVector[i]  && u < modalVector[i+1] ) return 1.f;
    else                    return 0.f;
  }
  else{
    return ((u-modalVector[i])/(modalVector[i+k-1] - modalVector[i])) * bsplineFunction(u,k-1,i,modalVector) + ((modalVector[i+k] - u)/(modalVector[i+k] - modalVector[i+1]))*bsplineFunction(u,k-1,i+1,modalVector);
  }
}


glm::vec3 BSpline2D::polynom(float u,float v) const {
  glm::vec3 acc=glm::vec3(0.f,0.f,0.f);
  for (int i = 0; i <= getNX() ; i++) {
    for (int j = 0; j <= getNY(); j++) {
      acc += bsplineFunction(u,getOrderKX(),i,_modalVectorX) * bsplineFunction(v,getOrderKY(),j,_modalVectorY) * _controlPoints[getIdx(i,j)];
      // std::cout << _controlPoints[getIdx(i,j)].x<< ","<< _controlPoints[getIdx(i,j)].y<< ","<< _controlPoints[getIdx(i,j)].z<< "," << '\n';
    }
    // std::cout << "/* message */" << '\n';
  }
  // std::cout << "ressssssssss=" << acc.x << " ; " <<acc.y << " ; " <<acc.z  << '\n';
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

  // std::cout << "/* message */" << '\n';
  for (size_t i = 0; i < pointsX; i++) {
    for (size_t j = 0; j < pointsY; j++) {

      v = polynom(unitX*float(i)+minX,unitY*float(j)+minY);
      // std::cout << v.x<<","<< v.y<< ","<< v.z << '\t';
      vertices.push_back(v);
    }
    // std::cout  << '\n';
  }
}
