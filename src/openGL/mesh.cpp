#include "glm/glm.hpp"
#include "openglmain.h"

#include <memory>
#include <functional>
#include "mesh.h"


Mesh::Mesh(){
  // Initialise geometric data
  _vertices.push_back(glm::vec3(0.5f,  0.5f, 0.0f));  // Top Right
  _vertices.push_back(glm::vec3(0.5f,  -0.5f, 0.0f));  // Bottom Right
  _vertices.push_back(glm::vec3(-0.5f,  -0.5f, 0.0f)); // Bottom Left
  _vertices.push_back(glm::vec3(-0.5f,  0.5f, 0.0f));  // Top Left



  _normals.push_back(glm::vec3( 0.577350269189626f, 0.577350269189626f, 0.577350269189626f   ));// Top Right
  _normals.push_back(glm::vec3( 0.577350269189626f, -0.577350269189626f, 0.577350269189626f  )); // Bottom Right
  _normals.push_back(glm::vec3( -0.577350269189626f, -0.577350269189626f, 0.577350269189626f )); // Bottom Left
  _normals.push_back(glm::vec3( -0.577350269189626f, 0.577350269189626f, 0.577350269189626f   )); // Top Left

// TODO
  // _indices.push_back(Triangle(0,1,3));
  // _indices.push_back(Triangle(1,2,3));

  _indices = {
      // Note that we start from 0!
      0, 1, 3,   // First Triangle
      1, 2, 3    // Second Triangle
  };

}

Mesh::~Mesh(){
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_nbo);
  glDeleteBuffers(1, &_ebo);
  glDeleteVertexArrays(1, &_vao) ;
}

void Mesh::draw(){
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

void Mesh::initializeGeometry(){

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
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof (Triangle), _indices.data(), GL_STATIC_DRAW);
  //6. Unbind the VAO
  glBindVertexArray(0);

  std::cout << sizeof (Triangle)<<"  " << 3* sizeof (GLuint)   << '\n';



}
