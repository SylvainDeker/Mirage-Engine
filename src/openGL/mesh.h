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

  struct Triangle{
    Triangle(GLuint a, GLuint b, GLuint c){
      vertice[0] = a;
      vertice[1] = b;
      vertice[2] = c;
    }
    GLuint vertice[3];
  };

protected:

  // A simple geometry
  std::vector<glm::vec3> _vertices;
  std::vector<glm::vec3> _normals;
  std::vector<GLuint> _indices;

private:
  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _nbo;
  GLuint _ebo;


};





#endif // MESH_H
