#include "glm/glm.hpp"

#include "../nurbs/NURBS.hpp"
#include "../openGL/Shader.hpp"
#include <memory>
#include <functional>
#include "CubeMap.hpp"
#include "../light/Light.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"
#include "../openGL/stb_image.h"


CubeMap::CubeMap(const std::map<std::string,Shader*> & shaders):DeprecatedMesh(shaders){

}




CubeMap::~CubeMap(){
  glDeleteVertexArrays(1, &_cubeVAO);
  glDeleteVertexArrays(1, &_skyboxVAO);
  glDeleteBuffers(1, &_cubeVBO);
  glDeleteBuffers(1, &_skyboxVAO);
}



void CubeMap::draw(const DeprecatedDrawParameter & para){
  // _shaders.at("cubemaps")->use();
  // _shaders.at("cubemaps")->setInt("texture1", 0);

  _shaders.at("skybox")->use();
  _shaders.at("skybox")->setInt("skybox", 0);

  // _shaders.at("cubemaps")->use();
  // glm::mat4 model = para.model;
  // glm::mat4 view = para.camera->viewmatrix();
  // glm::mat4 projection = para.projection;
  // _shaders.at("cubemaps")->setMatrix4fv("model", model);
  // _shaders.at("cubemaps")->setMatrix4fv("view", view);
  // _shaders.at("cubemaps")->setMatrix4fv("projection", projection);
  // _shaders.at("cubemaps")->setVector3fv("cameraPos", para.camera->getPosition());
  // // cubes
  // glBindVertexArray(_cubeVAO);
  // glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, _cubeTexture);
  // glDrawArrays(GL_TRIANGLES, 0, 36);
  // glBindVertexArray(0);

  // draw skybox as last
  glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
  _shaders.at("skybox")->use();
  glm::mat4 view = glm::mat4(glm::mat3(para.camera->viewmatrix())); // remove translation from the view matrix
  _shaders.at("skybox")->setMatrix4fv("view", view);
  _shaders.at("skybox")->setMatrix4fv("projection", para.projection);
  // skybox cube
  glBindVertexArray(_skyboxVAO);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _cubemapTexture);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS); // set depth function back to default





}

void CubeMap::initializeGeometry(){

  // // positions          // texture Coords
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back(-1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(1.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(1.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back( 0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(0.0f);
  // _cubeVertices.push_back(-0.5f);_cubeVertices.push_back( 0.5f);_cubeVertices.push_back(-0.5f);     _cubeVertices.push_back( 0.0f); _cubeVertices.push_back( 1.0f); _cubeVertices.push_back( 0.0f);      _cubeVertices.push_back(0.0f);_cubeVertices.push_back(1.0f);
  //




  // positions
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f);
  _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f);
  _skyboxVertices.push_back( 1.0f); _skyboxVertices.push_back(-1.0f); _skyboxVertices.push_back( 1.0f);

  // // cube VAO
  // glGenVertexArrays(1, &_cubeVAO);
  // glGenBuffers(1, &_cubeVBO);
  // glBindVertexArray(_cubeVAO);
  // glBindBuffer(GL_ARRAY_BUFFER, _cubeVBO);
  // glBufferData(GL_ARRAY_BUFFER, _cubeVertices.size()*sizeof(float), _cubeVertices.data(), GL_STATIC_DRAW);
  // glEnableVertexAttribArray(0);
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  // glEnableVertexAttribArray(1);
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  // glEnableVertexAttribArray(2);
  // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  // skybox VAO
  glGenVertexArrays(1, &_skyboxVAO);
  glGenBuffers(1, &_skyboxVBO);
  glBindVertexArray(_skyboxVAO);
  glBindBuffer(GL_ARRAY_BUFFER, _skyboxVBO);
  glBufferData(GL_ARRAY_BUFFER, _skyboxVertices.size()*sizeof(float), _skyboxVertices.data(), GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

  // load textures
  // -------------

  _cubeTexture = loadTexture("../texture/wall.jpg");

  std::vector<std::string> faces
  {
    "../texture/skybox/right.jpg",
    "../texture/skybox/left.jpg",
    "../texture/skybox/top.jpg",
    "../texture/skybox/bottom.jpg",
    "../texture/skybox/front.jpg",
    "../texture/skybox/back.jpg"
  };

  _cubemapTexture = loadCubemap(faces);







}

// loads a cubemap texture from 6 individual texture faces
// order:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)
// -Z (back)
// -------------------------------------------------------
unsigned int CubeMap::loadCubemap(const std::vector<std::string> &faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);

        }
        else
        {
            std::cerr << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    return textureID;
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int CubeMap::loadTexture(char const * path)
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
