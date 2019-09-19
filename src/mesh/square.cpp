#include "square.h"


Square::Square():Mesh() {
  // Initialise geometric data
  float tmp = 0.1f;
  float dec =0.2f;
  _vertices.clear();
  _normals.clear();
  _indices.clear();

  _vertices.push_back(glm::vec3(tmp,  tmp, dec));  // Top Right
  _vertices.push_back(glm::vec3(tmp,  -tmp, dec));  // Bottom Right
  _vertices.push_back(glm::vec3(-tmp,  -tmp, dec)); // Bottom Left
  _vertices.push_back(glm::vec3(-tmp,  tmp, dec));  // Top Left


  _normals.push_back(glm::vec3( 0.577350269189626f, 0.577350269189626f, 0.577350269189626f   ));// Top Right
  _normals.push_back(glm::vec3( 0.577350269189626f, -0.577350269189626f, 0.577350269189626f  )); // Bottom Right
  _normals.push_back(glm::vec3( -0.577350269189626f, -0.577350269189626f, 0.577350269189626f )); // Bottom Left
  _normals.push_back(glm::vec3( -0.577350269189626f, 0.577350269189626f, 0.577350269189626f   )); // Top Left


  // _indices.push_back(Triangle(0,1,3));
  // _indices.push_back(Triangle(1,2,3));

  _indices = {
      // Note that we start from 0!
      0, 1, 3,   // First Triangle
      1, 2, 3    // Second Triangle
  };

}
