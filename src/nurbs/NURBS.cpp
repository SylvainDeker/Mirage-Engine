#include "NURBS.hpp"
#include "../glm/glm.hpp"
#include <vector>
#include <assert.h>




NURBS::NURBS(std::vector<glm::vec3>& controlPoints):
  _controlPoints(controlPoints),
  _order_k(1){

}


void NURBS::setOrderK(int k){
  assert(k>=1);
  _order_k = k;
}

int NURBS::getOrderK() const {
  return _order_k;
}

int NURBS::getN() const {
  assert(_controlPoints.size()>1);
  return _controlPoints.size()- 1;
}

void NURBS::setModalVector(){
  assert(getOrderK()>=1);
  assert(getN()>0);
  size_t node_number = getOrderK() + getN()+1;
  _modalVector.clear();
  for (size_t i = 0; i < node_number; i++) {
    _modalVector.push_back(float(i));
  }
}

void NURBS::setWeightVector(){
  _coef.clear();
  for (size_t i = 0; i < size_t(getN()+1); i++) {
    _coef.push_back(1.0f);
  }
}

void NURBS::setWeightVector(const std::vector<float> & coef){
  _coef = coef; // copy
}

float NURBS::recFloraison(float u,int k,int i) const {
  assert(u>=0.f);
  assert(k>0);

  if(k==1){
    if( u >=_modalVector[i]  && u < _modalVector[i+1] ) return 1.f;
    else                    return 0.f;
  }
  else{
    return ((u-_modalVector[i])/(_modalVector[i+k-1] - _modalVector[i])) * recFloraison(u,k-1,i) + ((_modalVector[i+k] - u)/(_modalVector[i+k] - _modalVector[i+1]))*recFloraison(u,k-1,i+1);
  }
}


glm::vec3 NURBS::polynom(float u) const {
  glm::vec3 acc=glm::vec3(0.f,0.f,0.f);
  float deno=0.f;
  float nki = 0;
  for (int i = 0; i <=getN() ; i++) {
    nki = recFloraison(u,getOrderK(),i);
    acc += nki * _controlPoints[i] *_coef[i] ;
    deno += nki * _coef[i] ;
  }
  return acc/deno;
}


glm::vec3 NURBS::floraison(float u) const {

  int dec = 0;
  int k_it = getOrderK();

  while(_modalVector[k_it]<u){
    ++dec;
    ++k_it;
  }

  std::vector<glm::vec3> pt = _controlPoints; // make a copy
  std::vector<glm::vec3> releventPoints;
  for(int i = 0; i < getOrderK(); i++){
    glm::vec3 p = pt[i+dec];
    releventPoints.push_back(p);
  }

  int l = getOrderK();
  for(int j = 0; j < getOrderK()-1 ; j++ ){
    for(int i = 0; i < l-1 ; i++ ){
      releventPoints[i] = (_modalVector[dec+l+i]-u) / (_modalVector[dec+l+i]-_modalVector[dec+1+i])*releventPoints[i] + (u-_modalVector[dec+1+i]) / (_modalVector[dec+l+i]-_modalVector[dec+1+i])*releventPoints[i+1];
    }
    l--;
    dec++;
  }

  return releventPoints[0];
}





void NURBS::getDisplayPoints(std::vector<glm::vec3> & vertices,size_t points) const {
  assert(int(_modalVector.size())==getOrderK()+getN()+1);
  float min = _modalVector[getOrderK()-1];
  float max = _modalVector[getN()+1];
  float dist = max-min;
  float unit = dist/float(points);
  glm::vec3 v;

  for (size_t i = 0; i < points; i++) {

    // Recursive calcul
    v = polynom(unit*float(i)+min);

    vertices.push_back(v);
  }
}
