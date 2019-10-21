#ifndef DRAWELEMENT_H_
#define DRAWELEMENT_H_

#include <vector>
#include "programGL.hpp"
#include "opengl_stuff.h"

struct DrawElement{
  DrawElement(const std::vector<ProgramGL> & progGL, const glm::mat4 & model,const glm::mat4 & view,const glm::mat4 & projection):
  progGL(progGL),model(model),view(view),projection(projection){
  }
  const std::vector<ProgramGL> & progGL;
  const glm::mat4 & model;
  const glm::mat4 & view;
  const glm::mat4 & projection;
};


#endif
