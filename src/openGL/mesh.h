#ifndef MESH_H
#define MESH_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "openglmain.h"


class Mesh {
public:
  Mesh();
  ~Mesh();

  void initializeGeometry();

  void draw();

private:

  // A simple geometry
  std::vector<GLfloat> _vertices;
  std::vector<GLfloat> _normals;
  std::vector<GLuint> _indices;

  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _nbo;
  GLuint _ebo;


};





#endif // MESH_H
