#include "glm/glm.hpp"

#include "../bspline/Bspline.hpp"
#include "../openGL/Shader.hpp"
#include <memory>
#include <functional>
#include "Cube.hpp"


Cube::Cube(){

}




Cube::~Cube(){
  glDeleteBuffers(1, &_vbo);
  glDeleteVertexArrays(1, &_vao) ;
}




void Cube::draw(const std::vector<Shader*> & shader,
          const glm::mat4 & model,
          const glm::mat4 & view,
          const glm::mat4 & projection){

  shader.at(1)->use();

  shader.at(1)->setMatrix4fv("model",model);
  shader.at(1)->setMatrix4fv("view",view);
  shader.at(1)->setMatrix4fv("projection",projection);

  shader.at(1)->setVector4fv("ourColor",glm::vec4(1.0, 0.5, 0.31 ,1.0));

   // render the cube
   glBindVertexArray(_vao);
   glDrawArrays(GL_TRIANGLES, 0, 36);



}

void Cube::initializeGeometry(const glm::vec3& pos){

  float value = 0.1;

    _vertices.push_back(glm::vec3(-value+pos.x, -value, -value));
    _vertices.push_back(glm::vec3( value+pos.x, -value, -value));
    _vertices.push_back(glm::vec3( value+pos.x,  value, -value));
    _vertices.push_back(glm::vec3( value+pos.x,  value, -value));
    _vertices.push_back(glm::vec3(-value+pos.x,  value, -value));
    _vertices.push_back(glm::vec3(-value+pos.x, -value, -value));

    _vertices.push_back(glm::vec3(-value, -value,  value));
    _vertices.push_back(glm::vec3( value, -value,  value));
    _vertices.push_back(glm::vec3( value,  value,  value));
    _vertices.push_back(glm::vec3( value,  value,  value));
    _vertices.push_back(glm::vec3(-value,  value,  value));
    _vertices.push_back(glm::vec3(-value, -value,  value));

    _vertices.push_back(glm::vec3(-value,  value,  value));
    _vertices.push_back(glm::vec3(-value,  value, -value));
    _vertices.push_back(glm::vec3(-value, -value, -value));
    _vertices.push_back(glm::vec3(-value, -value, -value));
    _vertices.push_back(glm::vec3(-value, -value,  value));
    _vertices.push_back(glm::vec3(-value,  value,  value));

     _vertices.push_back(glm::vec3(value,  value,  value));
     _vertices.push_back(glm::vec3(value,  value, -value));
     _vertices.push_back(glm::vec3(value, -value, -value));
     _vertices.push_back(glm::vec3(value, -value, -value));
     _vertices.push_back(glm::vec3(value, -value,  value));
     _vertices.push_back(glm::vec3(value,  value,  value));

    _vertices.push_back(glm::vec3(-value, -value, -value));
    _vertices.push_back(glm::vec3( value, -value, -value));
    _vertices.push_back(glm::vec3( value, -value,  value));
    _vertices.push_back(glm::vec3( value, -value,  value));
    _vertices.push_back(glm::vec3(-value, -value,  value));
    _vertices.push_back(glm::vec3(-value, -value, -value));

    _vertices.push_back(glm::vec3(-value,  value, -value));
    _vertices.push_back(glm::vec3( value,  value, -value));
    _vertices.push_back(glm::vec3( value,  value,  value));
    _vertices.push_back(glm::vec3( value,  value,  value));
    _vertices.push_back(glm::vec3(-value,  value,  value));
    _vertices.push_back(glm::vec3(-value,  value, -value));

    // first, configure the cube's VAO (and _vbo)

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(float)*3, _vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(_vao);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);





}
