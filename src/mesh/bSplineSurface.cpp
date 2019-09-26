#include "glm/glm.hpp"
#include "../openGL/openglmain.h"
#include "../bspline/bspline.hpp"

#include <memory>
#include <functional>
#include "bSplineSurface.h"


BSplineSurface::BSplineSurface(std::vector<glm::vec3> & vertices, size_t x, size_t y ):_vertices(vertices),_dimx(x),_dimy(y){

  // TODO TEMP
  float tmp = 0.1f;
  float dec = 0.1f;
  float decm = 0.5f;
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 5; j++) {
      _vertices.push_back(glm::vec3(float(i)*tmp,float(j)*tmp, decm) );
      // _vertices.push_back(glm::vec3(float(i)*tmp,float(j)*tmp, decm+dec*(glm::cos(float(i))+glm::sin(float(j))) ));
    }
  }
  // glm::vec3 norm;
  // for (size_t i = 0; i < 10; i++) {
  //   for (size_t j = 0; j < 10; j++) {
  //     norm = glm::cross()
  //     _normals.push_back(glm::vec3(float(i)*tmp,float(j)*tmp, decm+dec*(glm::cos(float(i))+glm::sin(float(j))) ));
  //   }
  // }
  // TODO TEMP
}


size_t BSplineSurface::getDimX() const {
  return _dimx;
}

size_t BSplineSurface::getDimY() const {
  return _dimy;
}

void BSplineSurface::setDimXY(size_t x, size_t y) {
  _dimx = x;
  _dimy = y;
}



BSplineSurface::~BSplineSurface(){
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_nbo);
  glDeleteBuffers(1, &_ebo);
  glDeleteVertexArrays(1, &_vao) ;
}




void BSplineSurface::draw(){
  glBindVertexArray(_vao);
  glDrawElements(GL_QUAD_STRIP, _indices.size(), GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

void BSplineSurface::initializeGeometry(){

  _indices.clear();
  for (size_t i = 0; i < _vertices.size(); i++) {
    _indices.push_back(i);
  }

  // Initialize the geometry
  // 1. Generate geometry buffers
  glGenBuffers(1, &_vbo) ;
  glGenBuffers(1, &_nbo) ;
  glGenBuffers(1, &_ebo) ;
  glGenVertexArrays(1, &_vao) ;
  // 2. Bind Vertex Array Object
  glBindVertexArray(_vao);
      // 3. Copy our vertices array in a buffer for OpenGL to use
      glBindBuffer(GL_ARRAY_BUFFER, _vbo);
      glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(glm::vec3), _vertices.data(), GL_STATIC_DRAW);
      // 4. Then set our vertex attributes pointers
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(0);
      // 5. Copy our normals array in a buffer for OpenGL to use
      glBindBuffer(GL_ARRAY_BUFFER, _nbo);
      glBufferData(GL_ARRAY_BUFFER, _normals.size()*sizeof (glm::vec3), _normals.data(), GL_STATIC_DRAW);
      // 6. Copy our vertices array in a buffer for OpenGL to use
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(1);
      // 7. Copy our index array in a element buffer for OpenGL to use
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof (GLuint), _indices.data(), GL_STATIC_DRAW);
  //6. Unbind the VAO
  glBindVertexArray(0);




}
