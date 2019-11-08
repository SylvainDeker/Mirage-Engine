#ifndef TEXTU_H_
#define TEXTU_H_

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "Mesh.hpp"
#include "../bspline/Bspline.hpp"
#include "../light/Light.hpp"

#include <memory>

class Textu : public Mesh {
public:
  Textu(const std::vector<Shader*> & shaders);
  ~Textu() override ;

  void initializeGeometry() override ;

  void draw(const DrawParameter & para) override ;


private:


  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
  GLuint _texture;
  GLuint _texture2;



};






#endif // TEXTU_H_
