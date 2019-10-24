#ifndef BSPLINELINE_H
#define BSPLINELINE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>

#include "../bspline/Bspline.hpp"
#include "../openGL/ProgramGL.hpp"
#include <memory>


class BSplineLine {
public:
  BSplineLine(std::vector<glm::vec3> & vertices);
  ~BSplineLine();

  void initializeGeometry();

  void draw(const std::vector<ProgramGL> & progGL,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection);



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
