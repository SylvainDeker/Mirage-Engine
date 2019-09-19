#ifndef MESH_H
#define MESH_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "openglmain.h"
#include <memory>

class Mesh {
public:
  Mesh();
  ~Mesh();

  void initializeGeometry();

  void draw();



  void addVertice(glm::vec3 vertice);
  void addNormal(glm::vec3 normal);
  void addTriangle(GLuint a,GLuint b,GLuint c);

private:
  // A simple geometry
  std::vector<glm::vec3> _vertices;
  std::vector<glm::vec3> _normals;
  std::vector<GLuint> _indices;

  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _nbo;
  GLuint _ebo;


};





#endif // MESH_H
