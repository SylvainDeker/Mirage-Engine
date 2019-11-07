#ifndef BSPLINELINE_H
#define BSPLINELINE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "../light/Light.hpp"
#include "../bspline/Bspline.hpp"
#include "../openGL/Shader.hpp"
#include <memory>
#include "Mesh.hpp"


class BSplineLine :public Mesh{
public:
  BSplineLine(std::vector<glm::vec3> & vertices);
  ~BSplineLine() override ;

  void initializeGeometry() override;

  void draw(const std::vector<Shader*> & shader,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection,
            const Light * light) override;



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
