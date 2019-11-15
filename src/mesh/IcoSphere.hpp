#ifndef ICOSPHERE_H
#define ICOSPHERE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "DeprecatedMesh.hpp"
#include "../nurbs/NURBS.hpp"
#include "../light/Light.hpp"
#include <memory>
#include "../openGL/DeprecatedDrawParameter.hpp"

class IcoSphere : public DeprecatedMesh{
public:
  IcoSphere(const std::map<std::string,Shader*> & shaders,unsigned int subdiv = 3);
  ~IcoSphere() override ;

  void initializeGeometry() override ;

  void draw(const DeprecatedDrawParameter & para) override ;


private:
  // A simple geometry
  std::vector<GLfloat> _vertices;
  std::vector<GLfloat> _normals;
  std::vector<GLuint> _indices;
  std::vector<GLuint> _index;

  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _nbo;
  GLuint _ebo;

  unsigned int _subdiv;



};






#endif // ICOSPHERE_H
