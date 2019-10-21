#ifndef CONTROLPOINTS_H
#define CONTROLPOINTS_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "../openGL/openglmain.h"
#include <memory>
#include "../openGL/drawElement.hpp"

class ControlPoints {
public:
  ControlPoints(std::vector<glm::vec3> & points);
  ~ControlPoints();

  void initializeGeometry();

  void draw(DrawElement de);


protected:
  // A simple geometry
  std::vector<glm::vec3> & _vertices;
  std::vector<glm::vec3> _normals;
  std::vector<GLuint> _indices;

  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;


};





#endif // CONTROLPOINTS_H
