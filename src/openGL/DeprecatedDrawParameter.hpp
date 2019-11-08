#ifndef DEPRECATEDDRAWPARAMETER_H_
#define DEPRECATEDDRAWPARAMETER_H_

#include "../openGL/opengl_stuff.h"
#include "../light/Light.hpp"
#include "Camera.hpp"


class DeprecatedDrawParameter{
public:

  DeprecatedDrawParameter(const glm::mat4 & mod,
                const Camera * cam,
                const glm::mat4 & proj,
                const Light * li) :
      model(mod),
      camera(cam),
      projection(proj),
      light(li)
                {


  }
  ~DeprecatedDrawParameter() = default;

  const glm::mat4 & model;
  const Camera * camera;
  const glm::mat4 & projection;
  const Light * light;
};

#endif // DRAWPARAMETER_H_
