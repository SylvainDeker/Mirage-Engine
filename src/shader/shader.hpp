#ifndef SHEDER_H_
#define SHEDER_H_

#include <iostream>

class Shader{
public:

  Shader();
  int setVertexShader(std::string vertexshader);



private:
  std::string readFile(std::string path) const;

  std::string _vertexShader;
  std::string _fragmentShader;


};


#endif // SHADER_H_
