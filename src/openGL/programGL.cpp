#include "programGL.hpp"
#include <cassert>
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
  }

  fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentshader, 1, &fragmentshader_source, NULL);
  glCompileShader(fragmentshader);
  glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &success);
  if(!success) {
      glGetShaderInfoLog(fragmentshader, 512, NULL, infoLog);
      std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
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
  }
  glDeleteShader(vertexshader);
  glDeleteShader(fragmentshader);

  return 0;

}


int ProgramGL::loadfile(std::string vertexshader_path, std::string fragmentshader_path){
  (void) vertexshader_path;
  (void) fragmentshader_path;
  // TODO put in file
  const char* vertexshader_source ="#version 410 core\n\
          layout (location = 0) in vec3 position;\n\
          layout (location = 1) in vec3 inormal;\n\
          uniform mat4 model;\n\
          uniform mat4 view;\n\
          uniform mat4 projection;\n\
          out vec3 normal;\n\
          void main()\n\
          {\n\
              // Note that we read the multiplication from right to left\n\
              gl_Position = projection * view * model * vec4(position, 1.0f);\n\
              normal = inormal;\n\
          }\n";

  const char* fragmentshader_source ="#version 410 core\n\
          in vec3 normal;\n\
          out vec4 color;\n\
          void main()\n\
          {\n\
              //color = vec4(vec3(clamp(dot(normalize(normal), vec3(0,0,1)), 0, 1)), 1.0);\n\
              color = vec4(normalize(normal)*0.5+0.5, 1.0);\n\
          }\n";


  return load(vertexshader_source,fragmentshader_source);
}


GLuint ProgramGL::getGLProgram() const { return _program;}


int ProgramGL::use(const glm::mat4 &model,const glm::mat4 &view,const glm::mat4 &projection) const {
  glUseProgram(_program);
  assert(getGLProgram()!=0);
  glUniformMatrix4fv( glGetUniformLocation(getGLProgram(), "model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv( glGetUniformLocation(getGLProgram(), "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv( glGetUniformLocation(getGLProgram(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

}
