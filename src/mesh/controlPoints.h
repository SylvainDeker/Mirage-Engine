#ifndef CONTROLPOINTS_H
#define CONTROLPOINTS_H

#include <vector>
#include "glm/glm.hpp"
#include "../openGL/opengl_stuff.h"
#include "../openGL/programGL.hpp"
#include <memory>


class ControlPoints {
public:
  ControlPoints(std::vector<glm::vec3> & points);
  ~ControlPoints();

  void initializeGeometry();

  void draw(const std::vector<ProgramGL> & progGL,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection);


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
