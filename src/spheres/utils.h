#ifndef UTILSPERSO_H
#define UTILSPERSO_H

#include <cassert>
#include <iostream>


GLfloat surfacetriangle(const glm::vec3 &a,const glm::vec3 &b,const glm::vec3 &c){

  glm::vec3 v1= b-a;
  glm::vec3 v2= c-a;
  return glm::abs(glm::length(glm::cross(v1,v2))) / 2.f;

}

glm::vec3 getCoord(const GLuint index_vertex,std::vector<GLfloat> &_vertices){

  return glm::vec3(_vertices[index_vertex*3+0],_vertices[index_vertex*3+1],_vertices[index_vertex*3+2]);
}

#endif
