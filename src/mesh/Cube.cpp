#include "glm/glm.hpp"

#include "../bspline/Bspline.hpp"
#include "../openGL/Shader.hpp"
#include <memory>
#include <functional>
#include "Cube.hpp"
#include "../light/Light.hpp"
#include "../openGL/DrawParameter.hpp"


Cube::Cube(const std::vector<Shader*> & shaders):Mesh(shaders){

}




Cube::~Cube(){
  glDeleteBuffers(1, &_vbo);
  glDeleteVertexArrays(1, &_vao) ;
}



void Cube::draw(const DrawParameter & para){

  _shaders.at(4)->use();
  // glCheckError();
  glCheckError();

  _shaders.at(4)->setMatrix4fv("model",para.model);
  _shaders.at(4)->setMatrix4fv("view",para.camera->viewmatrix());
  _shaders.at(4)->setMatrix4fv("projection",para.projection);
  _shaders.at(4)->setVector3fv("objectColor", glm::vec3(1.0f, 0.5f, 0.31f));
  _shaders.at(4)->setVector3fv("lightColor", para.light->getColor());
  _shaders.at(4)->setVector3fv("lightPos", para.light->getPosition());
  // _shaders.at(5)->setVector3fv("material.ambient", glm::vec3( 1.0f, 0.5f, 0.31f));
  // _shaders.at(5)->setVector3fv("material.diffuse", glm::vec3( 1.0f, 0.5f, 0.31f));
  // _shaders.at(5)->setVector3fv("material.specular",glm::vec3( 0.5f, 0.5f, 0.5f));
  // _shaders.at(5)->setFloat("material.shininess", 32.0f);

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
