#include "uv_spheres.h"
#include "utils.h"
#include <iostream>


/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------------------------------------------*/


#define deg2rad(x) float(M_PI)*(x)/180.f

static const char* vertexshader_source ="#version 410 core\n\
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

static const char* fragmentshader_source ="#version 410 core\n\
        in vec3 normal;\n\
        out vec4 color;\n\
        void main()\n\
        {\n\
            //color = vec4(vec3(clamp(dot(normalize(normal), vec3(0,0,1)), 0, 1)), 1.0);\n\
            color = vec4(normalize(normal)*0.5+0.5, 1.0);\n\
        }\n";


UVsphere::UVsphere(int width, int height) : OpenGLDemo(width, height), _activecamera(0), _camera(nullptr) {

    size_t scale_lat = 7;
    size_t scale_lon = scale_lat *2;
    float theta = 0;
    float phi = 0;
    float r = 0.5;
    float x,y,z;
    for(size_t i = 0; i < scale_lon; i++)
    {
        theta =  (float(i)*glm::pi<float>())*2/scale_lon;

        for(size_t j = 0; j < scale_lat; j++)
        {


            phi = (float(j+1)*glm::pi<float>())/(scale_lat+1);
            x = r * glm::sin(theta)*glm::sin(phi);
            y = r * glm::cos(phi);
            z = r * glm::cos(theta)*glm::sin(phi);

            _vertices.push_back(x);
            _vertices.push_back(y);
            _vertices.push_back(z);
            // printf("%f\t%f\t%f\n",x,y,z);

            _normals.push_back(x/r);
            _normals.push_back(y/r);
            _normals.push_back(z/r);

            if(j!=scale_lat-1){
                _indices.push_back((i*scale_lat+(j))%(scale_lat*scale_lon));
                _indices.push_back((i*scale_lat+(j)+1)%(scale_lat*scale_lon));
                _indices.push_back(((i+1)*scale_lat+(j))%(scale_lat*scale_lon));

                _indices.push_back(((i+1)*scale_lat+(j+1))%(scale_lat*scale_lon));
                _indices.push_back((i*scale_lat+j+1)%(scale_lat*scale_lon));
                _indices.push_back(((i+1)*scale_lat+(j))%(scale_lat*scale_lon));


            }
        }
    }

    x = 0;
    y = r;
    z = 0;
    _vertices.push_back(x);
    _vertices.push_back(y);
    _vertices.push_back(z);
    _normals.push_back(0);
    _normals.push_back(1);
    _normals.push_back(0);

    for(size_t i = 0; i < scale_lon; i++)
    {
        _indices.push_back(scale_lon*scale_lat);
        _indices.push_back(i*scale_lat);
        _indices.push_back( ((i+1)*scale_lat ) % (scale_lon*scale_lat)  );
    }


    x = 0;
    y = -r;
    z = 0;
    _vertices.push_back(x);
    _vertices.push_back(y);
    _vertices.push_back(z);
    _normals.push_back(0);
    _normals.push_back(-1);
    _normals.push_back(0);


    for(size_t i = 0; i < scale_lon; i++)
    {
        _indices.push_back(scale_lon*scale_lat+1);
        _indices.push_back(i*scale_lat+scale_lat-1);
        _indices.push_back( ((i+1)*scale_lat +scale_lat-1 ) % (scale_lon*scale_lat)  );
    }


    std::cout << "Nb Tiangle =" << _indices.size()/3 << '\n';

    glm::vec3 pta,ptb,ptc;
    GLfloat sum =0;
    for (size_t i = 0; i < _indices.size(); i+=3) {
       pta = getCoord(_indices[i+0],_vertices);
       ptb = getCoord(_indices[i+1],_vertices);
       ptc = getCoord(_indices[i+2],_vertices);
       sum += surfacetriangle(pta,ptb,ptc);
    }

    std::cout << "SUM Surfaces:"<< sum << '\n';
    std::cout << "Ideal sphere Surface:"<< 4*glm::pi<float>()*r*r << '\n';



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

    _cameraselector.push_back( []()->Camera*{return new EulerCamera(glm::vec3(0.f, 0.f, 1.f));} );
    _cameraselector.push_back( []()->Camera*{return new TrackballCamera(glm::vec3(0.f, 0.f, 1.f),glm::vec3(0.f, 1.f, 0.f),glm::vec3(0.f, 0.f, 0.f));} );

    _camera.reset(_cameraselector[_activecamera]());

    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _view = _camera->viewmatrix();

    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

UVsphere::~UVsphere() {
    glDeleteProgram(_program);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_nbo);
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao) ;
}

void UVsphere::resize(int width, int height){
    OpenGLDemo::resize(width, height);
    _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
    _projection = glm::perspective(_camera->zoom(), float(_width) / _height, 0.1f, 100.0f);
}

void UVsphere::draw() {
    OpenGLDemo::draw();

    glUseProgram(_program);

    _view = _camera->viewmatrix();

    glUniformMatrix4fv( glGetUniformLocation(_program, "model"), 1, GL_FALSE, glm::value_ptr(_model));
    glUniformMatrix4fv( glGetUniformLocation(_program, "view"), 1, GL_FALSE, glm::value_ptr(_view));
    glUniformMatrix4fv( glGetUniformLocation(_program, "projection"), 1, GL_FALSE, glm::value_ptr(_projection));

    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void UVsphere::mouseclick(int button, float xpos, float ypos) {
    _button = button;
    _mousex = xpos;
    _mousey = ypos;
    _camera->processmouseclick(_button, xpos, ypos);
}

void UVsphere::mousemove(float xpos, float ypos) {
    _camera->processmousemovement(_button, xpos, ypos, true);
}

void UVsphere::keyboardmove(int key, double time) {
    _camera->processkeyboard(Camera_Movement(key), time);
}

bool UVsphere::keyboard(unsigned char k) {
    switch(k) {
        case 'p':
            _activecamera = (_activecamera+1)%2;
            _camera.reset(_cameraselector[_activecamera]());
            _camera->setviewport(glm::vec4(0.f, 0.f, _width, _height));
            return true;
        default:
            return false;
    }
}
