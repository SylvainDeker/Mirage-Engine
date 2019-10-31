#include "Shader.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

Shader::Shader():_shaderID(0){
}


Shader::Shader(const Shader & copy):
                _shaderID(copy.getGLProgram()){

}



Shader::~Shader(){
  if(_shaderID >0 )
  glDeleteProgram(_shaderID);
}




int Shader::load(const char * vertexshader_source, const char * fragmentshader_source){
  assert(_shaderID ==0);
  // Initialize shaders
  GLint success;
  GLchar infoLog[512]; // warning fixed size ... request for LOG_LENGTH!!!
  GLuint vertexshader, fragmentshader;

  // 1. Generate the shader
  vertexshader = glCreateShader(GL_VERTEX_SHADER);
  // 2. set the source
  glShaderSource(vertexshader, 1, &vertexshader_source, NULL);
  // 3. Compile
  glCompileShader(vertexshader);
  // 4. test for compile error
  glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &success);
  if(!success) {
      glGetShaderInfoLog(vertexshader, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
      return 1;
  }

  fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentshader, 1, &fragmentshader_source, NULL);
  glCompileShader(fragmentshader);
  glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
  if(!success) {
      glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
      return 2;
  }

  // 1. Generate the program
  _shaderID = glCreateProgram();
  // 2. Attach the shaders to the program
  glAttachShader(_shaderID, vertexshader);
  glAttachShader(_shaderID, fragmentshader);
  // 3. Link the program
  glLinkProgram(_shaderID);
  // 4. Test for link errors
  glGetProgramiv(_shaderID, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(_shaderID, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
      return 3;
  }
  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader);

  return 0;

}


int Shader::loadfile(std::string vertexshader_path, std::string fragmentshader_path){
  (void) vertexshader_path;
  (void) fragmentshader_path;


   std::ifstream desc_vs(vertexshader_path);
   std::ifstream desc_fs(fragmentshader_path);

   std::string line;
   std::string vertexshader_source;
   std::string fragmentshader_source;

   if(desc_vs)
   {

      while(getline(desc_vs, line)){
        vertexshader_source += line + '\n';
      }
      vertexshader_source += '\0';

   }
   else   std::cerr << "ERROR: cannot read vertex shader file: "<< vertexshader_path << '\n';

   line = "";

   if(desc_fs)
   {

      while(getline(desc_fs, line)){
        fragmentshader_source += line + '\n';
      }
      fragmentshader_source += '\0';
   }
   else   std::cerr << "ERROR: cannot read fragment shader shader file: "<< fragmentshader_path << '\n';





   return load(vertexshader_source.c_str(),fragmentshader_source.c_str());




}


GLuint Shader::getGLProgram() const { return _shaderID;}


void Shader::use() const {
  assert(_shaderID > 0);
  glUseProgram(_shaderID);
}

void Shader::setBool(const std::string &name, bool value) const {
  int uniformLoc = glGetUniformLocation(getGLProgram(), name.c_str());
  // assert(uniformLoc != -1);
  glUniform1i(uniformLoc, (int)value);
}
void Shader::setInt(const std::string &name, int value) const {
  int uniformLoc = glGetUniformLocation(getGLProgram(), name.c_str());
  // assert(uniformLoc != -1);
  glUniform1i( uniformLoc, value);
}

void Shader::setFloat(const std::string &name, float value) const {
  int uniformLoc = glGetUniformLocation(getGLProgram(), name.c_str());
  // assert(uniformLoc != -1);
  glUniform1f(uniformLoc, value);
}

void Shader::setMatrix4fv(const std::string &name,const glm::mat4 &value) const{
  int uniformLoc = glGetUniformLocation(getGLProgram(), name.c_str());
  // assert(uniformLoc != -1);
  glUniformMatrix4fv( uniformLoc, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVector4fv(const std::string &name,const glm::vec4& value) const{
  int uniformLoc = glGetUniformLocation(getGLProgram(), name.c_str());
  // assert(uniformLoc != -1);
  glUniform4fv(uniformLoc,1,glm::value_ptr(value));
}
