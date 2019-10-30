#ifndef MAINSCENE_H
#define MAINSCENE_H


#include "Camera.hpp"

#include <memory>
#include <functional>
#include "../mesh/DemoBSplineLine.hpp"
#include "../mesh/DemoBSplineSurface.hpp"
#include "./Shader.hpp"


/** Simple drawing demonstration
 */
class MainScene{
public:
    explicit MainScene(int width, int height);
    ~MainScene() ;

    void resize(int width, int height) ;
    void draw() ;

    void mouseclick(int button, float xpos, float ypos) ;
    void mousemove(float xpos, float ypos) ;
    void keyboardmove(int key, double time) ;
    bool keyboard(unsigned char k) ;
    void toggledrawmode();

private:

    // // Shader program for rendering
    // GLuint _shaderID;


    // Width and heigth of the viewport
    int _width;
    int _height;

    bool _drawfill;
    std::vector<Shader> _shaders;
    // Rendering mode (true is filled, false is wireframed

    // for mouse management
    int _button; // 0 --> left. 1 --> right. 2 --> middle. 3 --> other
    float _mousex{0};
    float _mousey{0};

    // Camera
    using CameraSelector=std::function<Camera*()>;
    std::vector<CameraSelector> _cameraselector;
    unsigned int _activecamera;

    std::unique_ptr<Camera> _camera;

    // matrices
    glm::mat4 _model;
    glm::mat4 _view;
    glm::mat4 _projection;

    DemoBSplineLine _demoBSplineLine;
    DemoBSplineSurface _demoBSplineSurface;
};

/*------------------------------------------------------------------------------------------------------------------------*/


#endif // MAINSCENE_H
