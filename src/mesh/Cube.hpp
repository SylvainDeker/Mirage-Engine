#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "Mesh.hpp"
#include "../bspline/Bspline.hpp"

#include <memory>

class Cube : public Mesh{
public:
  Cube();
  ~Cube() override ;

  void initializeGeometry() override ;

  void draw(const std::vector<Shader*> & shader,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection) override ;


private:
  // A simple geometry
  std::vector<glm::vec3> _vertices;


  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;



};






#endif // CUBE_H
