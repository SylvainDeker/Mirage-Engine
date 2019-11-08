#include "glm/glm.hpp"
#include <cstdlib>
#include <ctime>
#include <memory>
#include <functional>
#include "ControlPoints.hpp"
#include "../openGL/opengl_stuff.h"
#include "../light/Light.hpp"
#include "../openGL/DrawParameter.hpp"


ControlPoints::ControlPoints(const std::vector<Shader*> & shaders, std::vector<glm::vec3> & points):DeprecatedMesh(shaders),_vertices(points){



}

ControlPoints::~ControlPoints(){
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ebo);
  glDeleteVertexArrays(1, &_vao) ;
}

void ControlPoints::draw(const DrawParameter & para){

  _shaders.at(3)->use();
  _shaders.at(3)->setMatrix4fv("model",para.model);
  _shaders.at(3)->setMatrix4fv("view",para.camera->viewmatrix());
  _shaders.at(3)->setMatrix4fv("projection",para.projection);
  float r = float(std::rand())/RAND_MAX;
  float g = float(std::rand())/RAND_MAX;
  float b = float(std::rand())/RAND_MAX;
  _shaders.at(3)->setVector4fv("usercolor",glm::vec4(r,g,b,1.0));

  glBindVertexArray(_vao);
  glDrawElements(GL_POINTS, _indices.size(), GL_UNSIGNED_INT, nullptr);
  glPointSize(10.0f);
  glBindVertexArray(0);
}

void ControlPoints::initializeGeometry(){

  for (size_t i = 0; i < _vertices.size(); i++) {
    _indices.push_back(int(i));
  }

  // Initialize the geometry
  // 1. Generate geometry buffers
  glGenBuffers(1, &_vbo) ;
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
