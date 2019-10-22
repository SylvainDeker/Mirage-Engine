#include "programGL.hpp"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>

ProgramGL::ProgramGL():_program(0){
}


ProgramGL::~ProgramGL(){
  glDeleteProgram(_program);
}




int ProgramGL::load(const char * vertexshader_source, const char * fragmentshader_source){

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
  _program = glCreateProgram();
  // 2. Attach the shaders to the program
  glAttachShader(_program, vertexshader);
  glAttachShader(_program, fragmentshader);
  // 3. Link the program
  glLinkProgram(_program);
  // 4. Test for link errors
  glGetProgramiv(_program, GL_LINK_STATUS, &success);
  if(!success) {
      glGetProgramInfoLog(_program, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
      return 3;
  }
  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader);

  return 0;

}


int ProgramGL::loadfile(std::string vertexshader_path, std::string fragmentshader_path){
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


GLuint ProgramGL::getGLProgram() const { return _program;}


void ProgramGL::use(const glm::mat4 &model,const glm::mat4 &view,const glm::mat4 &projection) const {
  glUseProgram(_program);
  assert(getGLProgram()!=0);
  glUniformMatrix4fv( glGetUniformLocation(getGLProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv( glGetUniformLocation(getGLProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv( glGetUniformLocation(getGLProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

}
