#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <vector>
#include "glm/glm.hpp"
#include <GL/gl.h>
#include "DeprecatedMesh.hpp"
#include "../nurbs/NURBS.hpp"
#include "../light/Light.hpp"
#include <memory>
#include "../openGL/DeprecatedDrawParameter.hpp"

class CubeMap : public DeprecatedMesh{
public:
  CubeMap(const std::map<std::string,Shader*> & shaders);
  ~CubeMap() override ;

  void initializeGeometry() override ;

  void draw(const DeprecatedDrawParameter & para) override ;


private:
  unsigned int loadCubemap(const std::vector<std::string> &faces);
  unsigned int loadTexture(char const * path);
  // A simple geometry
  std::vector<float> _cubeVertices;
  std::vector<float> _skyboxVertices;

  unsigned int _cubeTexture;
  unsigned int _cubemapTexture;


  // OpenGL object for geometry
  unsigned int _cubeVAO;
  unsigned int _cubeVBO;
  unsigned int _skyboxVAO;
  unsigned int _skyboxVBO;



};






#endif // CUBEMAP_H
