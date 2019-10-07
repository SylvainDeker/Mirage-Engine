#include "shader.hpp"
#include <fstream>
#include <iostream>

Shader::Shader(){


}

int Shader::setVertexShader(std::string vertexshader){
  _vertexShader = vertexshader;
  return 0;
}

std::string Shader::readFile(std::string path) const{
  std::string res;
  std::string cat;
  std::ifstream infile(path);
  while (std::getline(infile,cat)){
      res += cat;
  }
  return cat;
}
