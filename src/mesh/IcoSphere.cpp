#include "glm/glm.hpp"

#include "../nurbs/NURBS.hpp"
#include "../openGL/Shader.hpp"
#include <memory>
#include <functional>
#include "IcoSphere.hpp"
#include "../light/Light.hpp"
#include "../openGL/stb_image.h"
#include "../operation/SubDivide.hpp"


IcoSphere::IcoSphere(const std::map<std::string,Shader*> & shaders,unsigned int subdiv):DeprecatedMesh(shaders),_subdiv(subdiv){

}




IcoSphere::~IcoSphere(){

  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_nbo);
  glDeleteBuffers(1, &_ebo);
  glDeleteVertexArrays(1, &_vao) ;
}



void IcoSphere::draw(const DeprecatedDrawParameter & para){

    _shaders.at("normal")->use();
    _shaders.at("normal")->setMatrix4fv("model",para.model);
    _shaders.at("normal")->setMatrix4fv("view",para.camera->viewmatrix());
    _shaders.at("normal")->setMatrix4fv("projection",para.projection);

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

}

void IcoSphere::initializeGeometry(){
  float w = 0.1f;
  float l = w * (1.f+float(glm::sqrt(5.f)))/2.f;
  float dist = glm::sqrt(w*w+l*l+0*0);



  _vertices = { -w,0.f,l,
                 w,0.f,l,
                -w,0.f,-l,
                 w,0.f,-l,
                 0.f,l,w,
                 0.f,l,-w,
                 0.f,-l,w,
                 0.f,-l,-w,
                 l,w,0.f,
                 -l,w, 0.f,
                 l,-w,0.f,
                 -l,-w, 0.f  };

  _normals = { -w/dist,0.f,l/dist,
                w/dist,0.f,l/dist,
               -w/dist,0.f,-l/dist,
               w/dist,0.f,-l/dist,
               0.f,l/dist,w/dist,
              0.f,l/dist,-w/dist,
              0.f,-l/dist,w/dist,
              0.f,-l/dist,-w/dist,
               l/dist,w/dist,0.f,
               -l/dist,w/dist, 0.f,
               l/dist,-w/dist,0.f,
               -l/dist,-w/dist, 0.f  };

  _indices = { 0,4,1,
               0,9,4,
               9,5,4,
               4,5,8,
               4,8,1,
               8,10,1,
               8,3,10,
               5,3,8,
               5,2,3,
               2,7,3,
               7,10,3,
               7,6,10,
               7,11,6,
               11,0,6,
               0,1,6,
               6,1,10,
               9,0,11,
               9,11,2,
               9,2,5,
               7,2,11 };

  for (size_t i = 0; i < _subdiv; i++) {
    SubDivide sb(_vertices,_normals,_indices);
    sb.setCoef( glm::sqrt( w*w+l*l ) );
    sb.run();

  }
  // Initialize the geometry
  // 1. Generate geometry buffers
  glGenBuffers(1, &_vbo) ;
  glGenBuffers(1, &_nbo) ;
  glGenBuffers(1, &_ebo) ;
  glGenVertexArrays(1, &_vao) ;
  // 2. Bind Vertex Array Object
  glBindVertexArray(_vao);
      // 3. Copy our vertices array in a buffer for OpenGL to use
      glBindBuffer(GL_ARRAY_BUFFER, _vbo);
      glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof (GLfloat), _vertices.data(), GL_STATIC_DRAW);
      // 4. Then set our vertex attributes pointers
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(0);
      // 5. Copy our normals array in a buffer for OpenGL to use
      glBindBuffer(GL_ARRAY_BUFFER, _nbo);
      glBufferData(GL_ARRAY_BUFFER, _normals.size()*sizeof (GLfloat), _normals.data(), GL_STATIC_DRAW);
      // 6. Copy our vertices array in a buffer for OpenGL to use
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(1);
      // 7. Copy our index array in a element buffer for OpenGL to use
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof (GLfloat), _indices.data(), GL_STATIC_DRAW);
  //6. Unbind the VAO
  glBindVertexArray(0);


}
