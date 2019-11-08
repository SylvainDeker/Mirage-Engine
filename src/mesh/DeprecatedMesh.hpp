#ifndef DEPRECATED_H_
#define DEPRECATED_H_
#include <vector>
#include "../openGL/Shader.hpp"
#include "../openGL/DrawParameter.hpp"

class DeprecatedMesh {
public:
  DeprecatedMesh(const std::vector<Shader*> & shaders):_shaders(shaders) {}
  virtual ~DeprecatedMesh() {};

  virtual void initializeGeometry() = 0 ;

  virtual void draw(const DrawParameter & para)  = 0 ;

protected:
  const std::vector<Shader*> & _shaders;

};

#endif // DEPRECATED_H_
