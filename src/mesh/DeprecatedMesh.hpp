#ifndef DEPRECATED_H_
#define DEPRECATED_H_
#include <map>
#include "../openGL/Shader.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"

class DeprecatedMesh {
public:
  DeprecatedMesh(const std::map<std::string,Shader*> & shaders):_shaders(shaders) {}
  virtual ~DeprecatedMesh() {};

  virtual void initializeGeometry() = 0 ;

  virtual void draw(const DeprecatedDrawParameter & para)  = 0 ;

protected:
  const std::map<std::string,Shader*> & _shaders;

};

#endif // DEPRECATED_H_
