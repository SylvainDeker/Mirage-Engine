#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "DeprecatedMesh.hpp"
#include "../bspline/Bspline.hpp"
#include "../light/Light.hpp"
#include <memory>
#include "../openGL/DeprecatedDrawParameter.hpp"

class Cube : public DeprecatedMesh{
public:
  Cube(const std::map<std::string,Shader*> & shaders);
  ~Cube() override ;

  void initializeGeometry() override ;

  void draw(const DeprecatedDrawParameter & para) override ;


private:
  // A simple geometry
  std::vector<glm::vec3> _vertices;



  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;



};






#endif // CUBE_H
