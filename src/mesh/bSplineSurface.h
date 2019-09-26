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
  BSplineSurface(std::vector<glm::vec3> & vertices, size_t x=1, size_t y=1);
  ~BSplineSurface();

  void initializeGeometry();
  size_t getDimX() const ;
  size_t getDimY() const ;
  void setDimXY(size_t x, size_t y);

  void draw();


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

  size_t _dimx;
  size_t _dimy;


};






#endif // BSPLINESURFACE_H
