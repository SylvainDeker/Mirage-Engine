#ifndef PROGRAMGL_H_
#define PROGRAMGL_H_

#include <string>
#include "opengl_stuff.h"

class ProgramGL{
public:
  ProgramGL();
  ~ProgramGL();

  int load(const char * vertexshader_source, const char * fragmentshader_source );

  int loadfile(std::string vertexshader_path, std::string fragmentshader_path);

  GLuint getGLProgram() const ;

  void use(const glm::mat4 &model,const glm::mat4 &view,const glm::mat4 &projection) const ;


private:

  // Shader program for rendering
  GLuint _program;


};




#endif // PROGRAMGL_H_
