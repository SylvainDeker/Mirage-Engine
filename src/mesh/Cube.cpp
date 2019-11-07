#include "glm/glm.hpp"

#include "../bspline/Bspline.hpp"
#include "../openGL/Shader.hpp"
#include <memory>
#include <functional>
#include "Cube.hpp"
#include "../light/Light.hpp"


Cube::Cube(const std::vector<Shader*> & shaders):Mesh(shaders){

}




Cube::~Cube(){
  glDeleteBuffers(1, &_vbo);
  glDeleteVertexArrays(1, &_vao) ;
}




void Cube::draw(
          const glm::mat4 & model,
          const glm::mat4 & view,
          const glm::mat4 & projection,
          const Light * light){

  _shaders.at(4)->use();
  // glCheckError();
  glCheckError();

  _shaders.at(4)->setMatrix4fv("model",model);
  _shaders.at(4)->setMatrix4fv("view",view);
  _shaders.at(4)->setMatrix4fv("projection",projection);

  _shaders.at(4)->setVector3fv("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
  _shaders.at(4)->setVector3fv("lightColor", light->getColor());
  _shaders.at(4)->setVector3fv("lightPos", light->getPosition());

   // render the cube
   glBindVertexArray(_vao);
   glDrawArrays(GL_TRIANGLES, 0, 36);


}

void Cube::initializeGeometry(){


        _vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f, -1.0f));
        _vertices.push_back(glm::vec3( 0.5f, -0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f, -1.0f));
        _vertices.push_back(glm::vec3( 0.5f,  0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f, -1.0f));
        _vertices.push_back(glm::vec3( 0.5f,  0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f, -1.0f));
        _vertices.push_back(glm::vec3(-0.5f,  0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f, -1.0f));
        _vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f, -1.0f));

        _vertices.push_back(glm::vec3(-0.5f, -0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f,  1.0f));
        _vertices.push_back(glm::vec3( 0.5f, -0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f,  1.0f));
        _vertices.push_back(glm::vec3( 0.5f,  0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f,  1.0f));
        _vertices.push_back(glm::vec3( 0.5f,  0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f,  1.0f));
        _vertices.push_back(glm::vec3(-0.5f,  0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f,  1.0f));
        _vertices.push_back(glm::vec3(-0.5f, -0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f,  0.0f,  1.0f));

        _vertices.push_back(glm::vec3(-0.5f,  0.5f,  0.5f)); _vertices.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
        _vertices.push_back(glm::vec3(-0.5f,  0.5f, -0.5f)); _vertices.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
        _vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); _vertices.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
        _vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f)); _vertices.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
        _vertices.push_back(glm::vec3(-0.5f, -0.5f,  0.5f)); _vertices.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));
        _vertices.push_back(glm::vec3(-0.5f,  0.5f,  0.5f)); _vertices.push_back(glm::vec3(-1.0f,  0.0f,  0.0f));

         _vertices.push_back(glm::vec3(0.5f,  0.5f,  0.5f));  _vertices.push_back(glm::vec3(1.0f,  0.0f,  0.0f));
         _vertices.push_back(glm::vec3(0.5f,  0.5f, -0.5f));  _vertices.push_back(glm::vec3(1.0f,  0.0f,  0.0f));
         _vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));  _vertices.push_back(glm::vec3(1.0f,  0.0f,  0.0f));
         _vertices.push_back(glm::vec3(0.5f, -0.5f, -0.5f));  _vertices.push_back(glm::vec3(1.0f,  0.0f,  0.0f));
         _vertices.push_back(glm::vec3(0.5f, -0.5f,  0.5f));  _vertices.push_back(glm::vec3(1.0f,  0.0f,  0.0f));
         _vertices.push_back(glm::vec3(0.5f,  0.5f,  0.5f));  _vertices.push_back(glm::vec3(1.0f,  0.0f,  0.0f));

        _vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f, -1.0f,  0.0f));
        _vertices.push_back(glm::vec3( 0.5f, -0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f, -1.0f,  0.0f));
        _vertices.push_back(glm::vec3( 0.5f, -0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f, -1.0f,  0.0f));
        _vertices.push_back(glm::vec3( 0.5f, -0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f, -1.0f,  0.0f));
        _vertices.push_back(glm::vec3(-0.5f, -0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f, -1.0f,  0.0f));
        _vertices.push_back(glm::vec3(-0.5f, -0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f, -1.0f,  0.0f));

        _vertices.push_back(glm::vec3(-0.5f,  0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f,  1.0f,  0.0f));
        _vertices.push_back(glm::vec3( 0.5f,  0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f,  1.0f,  0.0f));
        _vertices.push_back(glm::vec3( 0.5f,  0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f,  1.0f,  0.0f));
        _vertices.push_back(glm::vec3( 0.5f,  0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f,  1.0f,  0.0f));
        _vertices.push_back(glm::vec3(-0.5f,  0.5f,  0.5f));  _vertices.push_back(glm::vec3(0.0f,  1.0f,  0.0f));
        _vertices.push_back(glm::vec3(-0.5f,  0.5f, -0.5f));  _vertices.push_back(glm::vec3(0.0f,  1.0f,  0.0f));
    // first, configure the cube's VAO (and _vbo)

    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*_vertices.size(),_vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(_vao);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);



}
