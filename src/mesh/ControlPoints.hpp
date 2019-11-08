#ifndef CONTROLPOINTS_H
#define CONTROLPOINTS_H

#include <vector>
#include "glm/glm.hpp"
#include "../openGL/opengl_stuff.h"
#include "../openGL/Shader.hpp"
#include <memory>
#include "DeprecatedMesh.hpp"
#include "../light/Light.hpp"
#include "../openGL/DrawParameter.hpp"

class ControlPoints : public DeprecatedMesh {
public:
  ControlPoints(const std::vector<Shader*> & shaders, std::vector<glm::vec3> & points);
  ~ControlPoints() override ;

  void initializeGeometry() override ;

  void draw(const DrawParameter & para) override ;


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
