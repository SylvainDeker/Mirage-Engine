#ifndef MESH_H_
#define MESH_H_
#include <vector>
#include "../openGL/Shader.hpp"
#include "../openGL/opengl_stuff.h"
#include "../light/Light.hpp"
class Mesh {
public:

  virtual ~Mesh() {};

  virtual void initializeGeometry() = 0 ;

  virtual void draw(const std::vector<Shader*> & shader,
            const glm::mat4 & model,
            const glm::mat4 & view,
            const glm::mat4 & projection,
            const Light * light) = 0 ;


};

#endif // MESH_H_
