#ifndef DRAWPARAMETER_H_
#define DRAWPARAMETER_H_

#include "../openGL/opengl_stuff.h"
#include "../light/Light.hpp"
#include "../openGL/DrawParameter.hpp"
#include "Camera.hpp"


class DrawParameter{
public:

  DrawParameter(const Shader * s,
                const glm::mat4 & mod,
                const Camera * cam,
                const glm::mat4 & proj,
                const Light * li) :
      shader(s),
      model(mod),
      camera(cam),
      projection(proj),
      light(li)
                {


  }
  ~DrawParameter() = default;
  const Shader * shader;
  const glm::mat4 & model;
  const Camera * camera;
  const glm::mat4 & projection;
  const Light * light;
};

#endif // DRAWPARAMETER_H_
