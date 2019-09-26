#ifndef BSPLINESURFACE_H
#define BSPLINESURFACE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "../openGL/openglmain.h"
#include "../bspline/bspline.hpp"
#include <memory>

class BSplineSurface {
public:
  BSplineSurface(std::vector<glm::vec3> & vertices);
  ~BSplineSurface();

  void initializeGeometry();

  void draw();


  void addTriangle(GLuint a,GLuint b,GLuint c);

private:
  // A simple geometry
  std::vector<glm::vec3>& _vertices;
  std::vector<glm::vec3> _normals;
  std::vector<GLuint> _indices;

  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _nbo;
  GLuint _ebo;


};






#endif // BSPLINESURFACE_H
