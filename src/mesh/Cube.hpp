#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>

#include "../bspline/Bspline.hpp"

#include <memory>

class Cube {
public:
  Cube();
  ~Cube();

  void initializeGeometry(const glm::vec3& pos);

  void draw(const std::vector<Shader*> & shader,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection);


private:
  // A simple geometry
  std::vector<glm::vec3> _vertices;


  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;



};






#endif // CUBE_H
