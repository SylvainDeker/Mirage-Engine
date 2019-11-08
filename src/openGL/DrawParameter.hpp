#ifndef DRAWPARAMETER_H_
#define DRAWPARAMETER_H_

#include "../openGL/opengl_stuff.h"
#include "../light/Light.hpp"


class DrawParameter{
public:

  DrawParameter(const glm::mat4 & mod,
                const glm::mat4 & vie,
                const glm::mat4 & proj,
                const Light * li) :
      model(mod),
      view(vie),
      projection(proj),
      light(li)
                {


  }
  ~DrawParameter() = default;

  const glm::mat4 & model;
  const glm::mat4 & view;
  const glm::mat4 & projection;
  const Light * light;
};

#endif // DRAWPARAMETER_H_
