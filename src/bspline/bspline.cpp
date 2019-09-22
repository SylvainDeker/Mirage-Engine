#include "bspline.hpp"
#include "../glm/glm.hpp"
#include <vector>
#include <assert.h>
#include <iostream>




BSpline::BSpline(std::vector<glm::vec3>& controlPoints):
  _controlPoints(controlPoints),
  _order_k(1){

}


void BSpline::setOrderK(int k){
  assert(k>=1);
  _order_k = k;
}

int BSpline::getOrderK() const {
  return _order_k;
}

int BSpline::getN() const {
  assert(_controlPoints.size()>1);
  return _controlPoints.size()- 1;
}

void BSpline::setModalVector(){
  assert(getOrderK()>=1);
  assert(getN()>0);
  size_t node_number = getOrderK() + getN()+1;
  _modalVector.clear();
  for (size_t i = 0; i < node_number; i++) {
    _modalVector.push_back(float(i));
  }
}

float BSpline::bsplineFunction(float u,int k,int i) const {
  assert(u>=0.f);
  assert(k>0);

  if(k==1){
    if( u >=_modalVector[i]  && u < _modalVector[i+1] ) return 1.f;
    else                    return 0.f;
  }
  else{
    return ((u-_modalVector[i])/(_modalVector[i+k-1] - _modalVector[i])) * bsplineFunction(u,k-1,i) + ((_modalVector[i+k] - u)/(_modalVector[i+k] - _modalVector[i+1]))*bsplineFunction(u,k-1,i+1);
  }
}


glm::vec3 BSpline::polynom(float u) const {
  glm::vec3 acc=glm::vec3(0.f,0.f,0.f);
  for (int i = 0; i <=getN() ; i++) {
    // std::cout << u<<":"<<i << ":"<<bsplineFunction(u,getOrderK(),i) << '\n';
    acc += bsplineFunction(u,getOrderK(),i) * _controlPoints[i];
  }
  return acc;
}

void BSpline::getDisplayPoints(std::vector<glm::vec3> & vertices,size_t points) const {
  assert(int(_modalVector.size())==getOrderK()+getN()+1);
  float min = _modalVector[getOrderK()-1];
  float max = _modalVector[getN()+1];
  float dist = max-min;
  float unit = dist/float(points);
  glm::vec3 v;
  std::cout << "MAX=="<< max << '\n';
  for (size_t i = 0; i < points; i++) {
    // std::cout << "Pour u=" << unit*float(i) << " ";
    v = polynom(unit*float(i)+min);
    // std::cout << v.x << '\t'<< v.y << '\t' << '\n';
    vertices.push_back(v);
  }
}


void BSpline::checkmemory(){
  std::cout << "Order K="<< _order_k << '\n';
  std::cout << "N="<< getN() << '\n';
  std::cout << "Modal Vector: ";
  for (size_t i = 0; i < _modalVector.size(); i++) {
    std::cout << _modalVector[i] << ", ";
  }
  std::cout << '\n';

  std::cout << "Control Poitns" << '\n';
  for (size_t i = 0; i < _controlPoints.size(); i++) {
    std::cout << _controlPoints[i].x << '\t';
    std::cout << _controlPoints[i].y << '\t';
    std::cout << _controlPoints[i].z << '\n';
  }
}
