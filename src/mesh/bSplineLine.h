#ifndef BSPLINELINE_H
#define BSPLINELINE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "../openGL/openglmain.h"
#include "../bspline/bspline.hpp"
#include <memory>

class BSplineLine {
public:
  BSplineLine();
  ~BSplineLine();

  void initializeGeometry();

  void draw();



  void addVertice(glm::vec3 vertice);


protected:
  // A simple geometry
  std::vector<glm::vec3> _vertices;
  std::vector<GLuint> _indices;

  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;



};





#endif // BSPLINELINE_H
