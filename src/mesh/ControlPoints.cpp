#include "glm/glm.hpp"


#include <memory>
#include <functional>
#include "ControlPoints.hpp"
#include "../openGL/opengl_stuff.h"



ControlPoints::ControlPoints(std::vector<glm::vec3> & points):_vertices(points){



}

ControlPoints::~ControlPoints(){
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ebo);
  glDeleteVertexArrays(1, &_vao) ;
}

void ControlPoints::draw(const std::vector<Shader> & shader,
          const glm::mat4 & model,
          const glm::mat4 & view,
          const glm::mat4 & projection){
  shader.at(0).use();
  shader.at(0).setMatrix4fv("model",model);
  shader.at(0).setMatrix4fv("view",view);
  shader.at(0).setMatrix4fv("projection",projection);

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
