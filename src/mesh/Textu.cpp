#include "glm/glm.hpp"


#include "../openGL/Shader.hpp"
#include <memory>
#include <functional>
#include "Textu.hpp"
#include "../light/Light.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "../openGL/stb_image.h"
#include "../openGL/DrawParameter.hpp"


Textu::Textu(const std::vector<Shader*> & shaders):Mesh(shaders){

}




Textu::~Textu(){
  glDeleteBuffers(1, &_vbo);
  glDeleteVertexArrays(1, &_vao) ;
  glDeleteVertexArrays(1, &_ebo) ;
}




void Textu::draw(const DrawParameter & para){

  _shaders.at(2)->use();


  _shaders.at(2)->setMatrix4fv("model",para.model);
  _shaders.at(2)->setMatrix4fv("view",para.view);
  _shaders.at(2)->setMatrix4fv("projection",para.projection);
  _shaders.at(2)->setVector4fv("ourColor",glm::vec4(1.0, 0.5, 0.31 ,1.0));
  _shaders.at(2)->setInt("ourTexture",1);
  _shaders.at(2)->setInt("ourTexture2",1);
  glActiveTexture(GL_TEXTURE0); // activate the texture unit first before binding texture
  glBindTexture(GL_TEXTURE_2D, _texture);

  glActiveTexture(GL_TEXTURE1); // activate the texture unit first before binding texture
  glBindTexture(GL_TEXTURE_2D, _texture2);


  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


}

void Textu::initializeGeometry(){

  float vertices[] = {
      // positions          // colors           // texture coords
       0.5f, 0.0f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
       0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
      -0.5f, 0.0f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
      -0.5f, 0.0f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
  };
  unsigned int indices[] = {
      0, 1, 3, // first triangle
      1, 2, 3  // second triangle
  };

  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);
  glGenBuffers(1, &_ebo);

  glBindVertexArray(_vao);

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  // color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // load and create a texture
    // -------------------------

  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_2D, _texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  // load image, create texture and generate mipmaps
  int width, height, nrChannels;
  // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
  unsigned char *data = stbi_load("../texture/container.jpg", &width, &height, &nrChannels, 0);
  if (data)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
      std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);

  // TEXTURE 2
  glGenTextures(1, &_texture2);
  glBindTexture(GL_TEXTURE_2D, _texture2); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // stbi_set_flip_vertically_on_load(true);
  data = stbi_load("../texture/wall.jpg", &width, &height, &nrChannels, 0);
  if (data)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
      std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);






}
