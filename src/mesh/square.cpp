#include "square.h"


Square::Square():Mesh() {
  // Initialise geometric data
  float tmp = 0.1f;
  float dec =0.2f;

  addVertice(glm::vec3(tmp,  tmp, dec));  // Top Right
  addVertice(glm::vec3(tmp,  -tmp, dec));  // Bottom Right
  addVertice(glm::vec3(-tmp,  -tmp, dec)); // Bottom Left
  addVertice(glm::vec3(-tmp,  tmp, dec));  // Top Left


  addNormal(glm::vec3( 0.577350269189626f, 0.577350269189626f, 0.577350269189626f   ));// Top Right
  addNormal(glm::vec3( 0.577350269189626f, -0.577350269189626f, 0.577350269189626f  )); // Bottom Right
  addNormal(glm::vec3( -0.577350269189626f, -0.577350269189626f, 0.577350269189626f )); // Bottom Left
  addNormal(glm::vec3( -0.577350269189626f, 0.577350269189626f, 0.577350269189626f   )); // Top Left

  addTriangle(0,1,3);
  addTriangle(1,2,3);


}
