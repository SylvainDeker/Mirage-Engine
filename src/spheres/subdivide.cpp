#include <memory>
#include <functional>
#include <cassert>
#include "opengldemo.h"
#include "subdivide.hpp"





SubDivide::SubDivide(std::vector<GLfloat> & vertices,
  std::vector<GLfloat> & normals,
  std::vector<GLuint> &indices):
  _vertices(vertices),
  _normals(normals),
  _indices(indices),_coef(0){ }

void SubDivide::setCoef(const GLfloat coef){
  _coef = coef;
}

void SubDivide::run(){


  GLuint ai,bi,ci;
  GLuint di,ei,fi;

  for (size_t i = 0; i < _indices.size()/3; i++) {

    getIndexTriangle(i,ai,bi,ci);
    build_sub_triangle(ai,bi,ci,di,ei,fi);

    addTriangle(ai,fi,di);
    addTriangle(bi,di,ei);
    addTriangle(ci,ei,fi);
    addTriangle(di,ei,fi);
  }

  _indices = _newindices;
  _newindices.clear();

}

void SubDivide::build_sub_triangle(const GLuint index_vertex_a,
                                      const GLuint index_vertex_b,
                                      const GLuint index_vertex_c,
                                      GLuint & index_vertex_d,
                                      GLuint & index_vertex_e,
                                      GLuint & index_vertex_f){
  GLfloat dist = _coef;
  index_vertex_d = associateVertex(index_vertex_a,index_vertex_b,dist);
  index_vertex_e = associateVertex(index_vertex_b,index_vertex_c,dist);
  index_vertex_f = associateVertex(index_vertex_a,index_vertex_c,dist);


}

GLuint SubDivide::associateVertex(const GLuint index_vertex_a, const GLuint index_vertex_b,const GLfloat coef){
    GLuint index_vertex;
    if( ! findEdge(index_vertex_a,index_vertex_b,index_vertex)){
      SubDivide::Edge e;
      // glm::vec3 a = getCoord(index_vertex_a);
      // glm::vec3 b = getCoord(index_vertex_b);
      glm::vec3 na = getNorm(index_vertex_a);
      glm::vec3 nb = getNorm(index_vertex_b);

      glm::vec3 nd = glm::normalize(na+nb);
      glm::vec3 d = nd*coef;
      index_vertex = addVertex(d,nd);
      e.pt1 = index_vertex_a;
      e.pt2 = index_vertex_b;
      e.center = index_vertex;
      _indexEdge.push_back(e);
    }

    return index_vertex;

}


bool SubDivide::findEdge(const GLuint index_vertex_a,const GLuint index_vertex_b, GLuint & res){
  for (size_t i = 0; i < _indexEdge.size(); i++) {
    if( (_indexEdge[i].pt1==index_vertex_a && _indexEdge[i].pt2==index_vertex_b) ||
        (_indexEdge[i].pt2==index_vertex_a && _indexEdge[i].pt1==index_vertex_b) ){
          res = _indexEdge[i].center;
          return true;
        }
  }
  return false;
}


inline glm::vec3 SubDivide::getCoord(const GLuint index_vertex) const {
  assert(_vertices.size() == _normals.size());
  assert(index_vertex*3+2 < _vertices.size());
  assert(index_vertex*3+2 < _normals.size());
  return glm::vec3(_vertices[index_vertex*3+0],_vertices[index_vertex*3+1],_vertices[index_vertex*3+2]);
}

inline glm::vec3 SubDivide::getNorm(const GLuint index_vertex) const {
  assert(_vertices.size() == _normals.size());
  assert(index_vertex*3+2 < _vertices.size());
  assert(index_vertex*3+2 < _normals.size());
  return glm::vec3(_normals[index_vertex*3+0],_normals[index_vertex*3+1],_normals[index_vertex*3+2]);
}

inline void SubDivide::getIndexTriangle(const GLuint index_trinagle,GLuint &index_vertex1,GLuint &index_vertex2,GLuint &index_vertex3) const {
  index_vertex1 = _indices[index_trinagle*3+0];
  index_vertex2 = _indices[index_trinagle*3+1];
  index_vertex3 = _indices[index_trinagle*3+2];
}

inline void SubDivide::addTriangle(GLuint const index_vertex1,GLuint const index_vertex2,GLuint const index_vertex3){
  _newindices.push_back(index_vertex1);
  _newindices.push_back(index_vertex2);
  _newindices.push_back(index_vertex3);
}
inline GLuint SubDivide::addVertex(const glm::vec3 coord,const glm::vec3 norm){
  assert(_vertices.size() == _normals.size());
  _vertices.push_back(coord.x);
  _vertices.push_back(coord.y);
  _vertices.push_back(coord.z);
  _normals.push_back(norm.x);
  _normals.push_back(norm.y);
  _normals.push_back(norm.z);
  size_t index_vertex = (_vertices.size())/3 -1;;
  assert(getCoord(index_vertex)==coord && getNorm(index_vertex)==norm );
  return index_vertex;
}
