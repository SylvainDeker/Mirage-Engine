#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include "opengl_stuff.h"

class Shader{
public:
  Shader();
  ~Shader();

  int load(const char * vertexshader_source, const char * fragmentshader_source );

  int loadfile(std::string vertexshader_path, std::string fragmentshader_path);

  GLuint getGLProgram() const ;

  void use() const ;

  // utility uniform functions
  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setMatrix4fv(const std::string &name,const glm::mat4& value) const;

private:

  // Shader program for rendering
  GLuint _shaderID;


};




#endif // SHADER_H_
