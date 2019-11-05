#ifndef TEXTU_H_
#define TEXTU_H_

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>

#include "../bspline/Bspline.hpp"

#include <memory>

class Textu {
public:
  Textu();
  ~Textu();

  void initializeGeometry();

  void draw(const std::vector<Shader*> & shader,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection);


private:


  // OpenGL object for geometry
  GLuint _vao;
  GLuint _vbo;
  GLuint _ebo;
  GLuint _texture;



};






#endif // TEXTU_H_
