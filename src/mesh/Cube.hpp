#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "DeprecatedMesh.hpp"
#include "../bspline/Bspline.hpp"
#include "../light/Light.hpp"
#include <memory>
#include "../openGL/DrawParameter.hpp"

class Cube : public DeprecatedMesh{
public:
  Cube(const std::vector<Shader*> & shaders);
  ~Cube() override ;

  void initializeGeometry() override ;

  void draw(const DrawParameter & para) override ;


private:
  // A simple geometry
  std::vector<glm::vec3> _vertices;



  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;



};






#endif // CUBE_H
