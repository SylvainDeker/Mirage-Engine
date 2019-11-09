#ifndef BSPLINELINE_H
#define BSPLINELINE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "../light/Light.hpp"
#include "../bspline/Bspline.hpp"
#include "../openGL/Shader.hpp"
#include <memory>
#include "DeprecatedMesh.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"


class BSplineLine :public DeprecatedMesh{
public:
  BSplineLine(const std::map<std::string,Shader*> & shaders, std::vector<glm::vec3> & vertices);
  ~BSplineLine() override ;

  void initializeGeometry() override;

  void draw(const DeprecatedDrawParameter & para) override ;



  void addVertice(glm::vec3 vertice);


protected:
  // A simple geometry
  std::vector<glm::vec3> & _vertices;
  std::vector<GLuint> _indices;

  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;



};





#endif // BSPLINELINE_H
