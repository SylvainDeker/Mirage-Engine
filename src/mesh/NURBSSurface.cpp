#include "glm/glm.hpp"
#include "../light/Light.hpp"
#include "../nurbs/NURBS.hpp"
#include "../openGL/Shader.hpp"
#include <memory>
#include <functional>
#include "NURBSSurface.hpp"
#include "../openGL/DeprecatedDrawParameter.hpp"


NURBSSurface::NURBSSurface(const std::map<std::string,Shader*> & shaders,std::vector<glm::vec3> & vertices, size_t x, size_t y ):DeprecatedMesh(shaders),_vertices(vertices),_dimx(x),_dimy(y){

}


size_t NURBSSurface::getDimX() const {
  return _dimx;
}

size_t NURBSSurface::getDimY() const {
  return _dimy;
}

void NURBSSurface::setDimXY(size_t x, size_t y) {
  _dimx = x;
  _dimy = y;
}

glm::vec3 NURBSSurface::getVertice(size_t x,size_t y){

  assert(x<getDimX());
  assert(y<getDimY());
  size_t idx = getIdx(x,y);

  assert(idx<_vertices.size());
  return _vertices[idx];
}

size_t NURBSSurface::getIdx(size_t x,size_t y) const {
  assert(x<getDimX());
  assert(y<getDimY());
  size_t idx = x*getDimY()+y;

  return idx;
}


NURBSSurface::~NURBSSurface(){
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_nbo);
  glDeleteBuffers(1, &_ebo);
  glDeleteVertexArrays(1, &_vao) ;
}




void NURBSSurface::draw(const DeprecatedDrawParameter & para){

  _shaders.at("normal")->use();
  _shaders.at("normal")->setMatrix4fv("model",para.model);
  _shaders.at("normal")->setMatrix4fv("view",para.camera->viewmatrix());
  _shaders.at("normal")->setMatrix4fv("projection",para.projection);


  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
  glBindVertexArray(0);
}

void NURBSSurface::initializeGeometry(){

  _indices.clear();


  // Normals
  glm::vec3 norm;
  glm::vec3 e1,e2;
  for (size_t i = 0; i < getDimX(); i++) {
    for (size_t j = 0; j < getDimY(); j++) {
      if(j<getDimY()-1) e1 = getVertice(i,j) - getVertice(i,j+1);
      else e1 = getVertice(i,j-1) - getVertice(i,j);
      if(i<getDimX()-1) e2 = getVertice(i,j) - getVertice(i+1,j);
      else e2 = getVertice(i-1,j) - getVertice(i,j);


      norm = glm::cross(e1,e2);
      _normals.push_back(norm);
      if(i<getDimX()-1&&j<getDimY()-1){
        _indices.push_back(getIdx(i,j));
        _indices.push_back(getIdx(i,j+1));
        _indices.push_back(getIdx(i+1,j));

        _indices.push_back(getIdx(i+1,j+1));
        _indices.push_back(getIdx(i,j+1));
        _indices.push_back(getIdx(i+1,j));
      }
    }
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
      glBufferData(GL_ARRAY_BUFFER, _vertices.size()*sizeof(glm::vec3), _vertices.data(), GL_STATIC_DRAW);
      // 4. Then set our vertex attributes pointers
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(0);
      // 5. Copy our normals array in a buffer for OpenGL to use
      glBindBuffer(GL_ARRAY_BUFFER, _nbo);
      glBufferData(GL_ARRAY_BUFFER, _normals.size()*sizeof (glm::vec3), _normals.data(), GL_STATIC_DRAW);
      // 6. Copy our vertices array in a buffer for OpenGL to use
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
      glEnableVertexAttribArray(1);
      // 7. Copy our index array in a element buffer for OpenGL to use
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size()*sizeof (GLuint), _indices.data(), GL_STATIC_DRAW);
  //6. Unbind the VAO
  glBindVertexArray(0);


}
