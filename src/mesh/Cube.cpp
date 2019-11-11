#include "glm/glm.hpp"

#include "../nurbs/NURBS.hpp"
#include "../openGL/Shader.hpp"
#include <memory>
#include <functional>
#include "Cube.hpp"
#include "../light/Light.hpp"
#include "../openGL/stb_image.h"


Cube::Cube(const std::map<std::string,Shader*> & shaders):DeprecatedMesh(shaders){

}




Cube::~Cube(){
  glDeleteBuffers(1, &_vbo);
  glDeleteVertexArrays(1, &_vao) ;
}



void Cube::draw(const DeprecatedDrawParameter & para){

  // _shaders.at("l+m")->use();
  // // glCheckError();
  // glCheckError();
  //
  // // _shaders.at("l+m")->setMatrix4fv("model",para.model);
  // // _shaders.at("l+m")->setMatrix4fv("view",para.camera->viewmatrix());
  // // _shaders.at("l+m")->setMatrix4fv("projection",para.projection);
  // // _shaders.at("l+m")->setVector3fv("objectColor", glm::vec3(1.0f, 1.f, 1.f));
  // // _shaders.at("l+m")->setVector3fv("lightColor", para.light->getColor());
  // // _shaders.at("l+m")->setVector3fv("lightPos", para.light->getPosition());
  // // _shaders.at("l+m")->setVector3fv("viewPos", para.camera->getPosition());
  // // _shaders.at("l+m")->setVector3fv("material.ambient", glm::vec3( 1.0f, 0.5f, 0.31f));
  // // _shaders.at("l+m")->setVector3fv("material.diffuse", glm::vec3( 1.0f, 0.5f, 0.31f));
  // // _shaders.at("l+m")->setVector3fv("material.specular",glm::vec3( 0.5f, 0.5f, 0.5f));
  // // _shaders.at("l+m")->setFloat("material.shininess", 32.0f);
  // // _shaders.at("l+m")->setVector3fv("light.ambient", glm::vec3( 0.2f, 0.2f, 0.2f));
  // // _shaders.at("l+m")->setVector3fv("light.diffuse", glm::vec3( 0.5f, 0.5f, 0.5f)); // darken the light a bit to fit the scene
  // // _shaders.at("l+m")->setVector3fv("light.specular",glm::vec3( 1.0f, 1.0f, 1.0f));
  //
  //  // render the cube
  //  glBindVertexArray(_vao);
  //  glDrawArrays(GL_TRIANGLES, 0, 36);

   _shaders.at("cubemaps")->use();
   _shaders.at("cubemaps")->setInt("texture1", 0);

   _shaders.at("cubemaps")->use();
   glm::mat4 view = para.camera->viewmatrix();
   glm::mat4 projection = para.projection;
   _shaders.at("cubemaps")->setMatrix4fv("model", para.model);
   _shaders.at("cubemaps")->setMatrix4fv("view", view);
   _shaders.at("cubemaps")->setMatrix4fv("projection", projection);
   _shaders.at("cubemaps")->setVector3fv("cameraPos", para.camera->getPosition());
   // cubes
   glBindVertexArray(_vao);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, _cubeTexture);
   glDrawArrays(GL_TRIANGLES, 0, 36);
   glBindVertexArray(0);


}

void Cube::initializeGeometry(){


  // positions          // texture Coords
  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back(-1.0f);      _vertices.push_back(0.0f);_vertices.push_back(0.0f);
  _vertices.push_back( 0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back(-1.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);
  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back(-1.0f);      _vertices.push_back(1.0f);_vertices.push_back(1.0f);
  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back(-1.0f);      _vertices.push_back(1.0f);_vertices.push_back(1.0f);
  _vertices.push_back(-0.5f);_vertices.push_back( 0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back(-1.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);
  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back(-1.0f);      _vertices.push_back(0.0f);_vertices.push_back(0.0f);

  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back( 1.0f);      _vertices.push_back(0.0f);_vertices.push_back(0.0f);
  _vertices.push_back( 0.5f);_vertices.push_back(-0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back( 1.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);
  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back( 1.0f);      _vertices.push_back(1.0f);_vertices.push_back(1.0f);
  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back( 1.0f);      _vertices.push_back(1.0f);_vertices.push_back(1.0f);
  _vertices.push_back(-0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back( 1.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);
  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 0.0f); _vertices.push_back( 1.0f);      _vertices.push_back(0.0f);_vertices.push_back(0.0f);

  _vertices.push_back(-0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back(-1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);
  _vertices.push_back(-0.5f);_vertices.push_back( 0.5f);_vertices.push_back(-0.5f);     _vertices.push_back(-1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(1.0f);
  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back(-1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);
  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back(-1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);
  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back( 0.5f);     _vertices.push_back(-1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(0.0f);
  _vertices.push_back(-0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back(-1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);

  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);
  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(1.0f);
  _vertices.push_back( 0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);
  _vertices.push_back( 0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);
  _vertices.push_back( 0.5f);_vertices.push_back(-0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(0.0f);
  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 1.0f); _vertices.push_back( 0.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);

  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back(-1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);
  _vertices.push_back( 0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back(-1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(1.0f);
  _vertices.push_back( 0.5f);_vertices.push_back(-0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back(-1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);
  _vertices.push_back( 0.5f);_vertices.push_back(-0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back(-1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);
  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back(-1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(0.0f);
  _vertices.push_back(-0.5f);_vertices.push_back(-0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back(-1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);

  _vertices.push_back(-0.5f);_vertices.push_back( 0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);
  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(1.0f);
  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);
  _vertices.push_back( 0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(1.0f);_vertices.push_back(0.0f);
  _vertices.push_back(-0.5f);_vertices.push_back( 0.5f);_vertices.push_back( 0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(0.0f);
  _vertices.push_back(-0.5f);_vertices.push_back( 0.5f);_vertices.push_back(-0.5f);     _vertices.push_back( 0.0f); _vertices.push_back( 1.0f); _vertices.push_back( 0.0f);      _vertices.push_back(0.0f);_vertices.push_back(1.0f);



    // // first, configure the cube's VAO (and _vbo)
    //
    // glGenVertexArrays(1, &_vao);
    // glGenBuffers(1, &_vbo);
    //
    // glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*_vertices.size(),_vertices.data(), GL_STATIC_DRAW);
    //
    // glBindVertexArray(_vao);
    //
    // // position attribute
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    // glEnableVertexAttribArray(0);
    // // normal attribute
    // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    // cube VAO
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(float), _vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    _cubeTexture = loadTexture("../texture/wall.jpg");

}


unsigned int Cube::loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "[CubeMap] Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
