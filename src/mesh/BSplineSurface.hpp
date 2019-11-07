#ifndef BSPLINESURFACE_H
#define BSPLINESURFACE_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "Mesh.hpp"
#include "../bspline/Bspline.hpp"
#include "../light/Light.hpp"
#include <memory>

class BSplineSurface : public Mesh {
public:
  BSplineSurface(std::vector<glm::vec3> & vertices, size_t x=1, size_t y=1);
  ~BSplineSurface() override ;

  void initializeGeometry() override ;
  size_t getDimX() const ;
  size_t getDimY() const ;
  void setDimXY(size_t x, size_t y);
  glm::vec3 getVertice(size_t x,size_t y);
  size_t getIdx(size_t x, size_t y) const ;
  void draw(const std::vector<Shader*> & shader,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection,
            const Light * light) override ;


private:
  // A simple geometry
  std::vector<glm::vec3>& _vertices;
  std::vector<glm::vec3> _normals;
  std::vector<GLuint> _indices;

  // Shader program for rendering
  GLuint _shaderID;

  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _nbo;
  GLuint _ebo;

  size_t _dimx;
  size_t _dimy;


};






#endif // BSPLINESURFACE_H
