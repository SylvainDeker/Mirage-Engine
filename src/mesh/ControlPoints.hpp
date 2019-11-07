#ifndef CONTROLPOINTS_H
#define CONTROLPOINTS_H

#include <vector>
#include "glm/glm.hpp"
#include "../openGL/opengl_stuff.h"
#include "../openGL/Shader.hpp"
#include <memory>
#include "Mesh.hpp"
#include "../light/Light.hpp"

class ControlPoints : public Mesh {
public:
  ControlPoints(std::vector<glm::vec3> & points);
  ~ControlPoints() override ;

  void initializeGeometry() override ;

  void draw(const std::vector<Shader*> & shader,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection,
            const Light * light) override ;


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
