#include "glm/glm.hpp"
#include "../openGL/openglmain.h"
#include "../bspline/bspline.hpp"

#include <memory>
#include <functional>
#include "bSplineLine.h"


BSplineLine::BSplineLine(){
  float tmp = 0.1f;
  float dec =0.5f;

  addVertice(glm::vec3(tmp,  tmp, dec));  // Top Right
  addVertice(glm::vec3(tmp,  -tmp, dec));  // Bottom Right
  addVertice(glm::vec3(-tmp,  -tmp, dec)); // Bottom Left
  addVertice(glm::vec3(-tmp,  tmp, dec));  // Top Left


  _indices.push_back(0);
  _indices.push_back(1);
  _indices.push_back(2);
  _indices.push_back(3);


}


BSplineLine::~BSplineLine(){
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ebo);
  glDeleteVertexArrays(1, &_vao) ;
}

void BSplineLine::addVertice(glm::vec3 vertice){
  _vertices.push_back(vertice);  // Top Right
}




void BSplineLine::draw(){
  glBindVertexArray(_vao);
  glDrawElements(GL_LINE_STRIP, _indices.size(), GL_UNSIGNED_INT, nullptr);
  glPointSize(10.0f);
  glBindVertexArray(0);
}

void BSplineLine::initializeGeometry(){

  // Initialize the geometry
  // 1. Generate geometry buffers
  glGenBuffers(1, &_vbo) ;
  // glGenBuffers(1, &_nbo) ;
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
      // glBindBuffer(GL_ARRAY_BUFFER, _nbo);
      // glBufferData(GL_ARRAY_BUFFER, _normals.size()*sizeof (glm::vec3), _normals.data(), GL_STATIC_DRAW);
      // 6. Copy our vertices array in a buffer for OpenGL to use
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(1);
      // 7. Copy our index array in a element buffer for OpenGL to use
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof (GLuint), _indices.data(), GL_STATIC_DRAW);
  //6. Unbind the VAO
  glBindVertexArray(0);




}