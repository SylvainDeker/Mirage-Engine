#ifndef CONTROLPOINTS_H
#define CONTROLPOINTS_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "../openGL/openglmain.h"
#include <memory>

class ControlPoints {
public:
  ControlPoints();
  ~ControlPoints();

  void initializeGeometry();

  void draw();



  void addVertice(glm::vec3 vertice);
  void addNormal(glm::vec3 normal);
  void addTriangle(GLuint a,GLuint b,GLuint c);

protected:
  // A simple geometry
  std::vector<glm::vec3> _vertices;
  std::vector<glm::vec3> _normals;
  std::vector<GLuint> _indices;

  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _nbo;
  GLuint _ebo;


};





#endif // CONTROLPOINTS_H
