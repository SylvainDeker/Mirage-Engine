#ifndef  LIGHT_H_
#define LIGHT_H_

#include "glm/glm.hpp"

class Light {
public:

  Light(const glm::vec3 & color = glm::vec3(1.0f,1.0f,1.0f),glm::vec3 position = glm::vec3(0.0f,0.0f,0.0f)):
    _color(color),
    _position(position){}

  virtual ~Light() = default;

  inline const glm::vec3& getColor() const { return _color; }
  inline const glm::vec3& setColor( const glm::vec3& color ) { return _color = color; }

  inline const glm::vec3& getPosition() const { return _position; }
  inline const glm::vec3& SetPosition( const glm::vec3& position ) { return _position = position; }

private:
  glm::vec3 _color;
  glm::vec3 _position;


};

#endif // LIGHT_H_
