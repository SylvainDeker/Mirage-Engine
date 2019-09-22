#ifndef MAINSCENE_H
#define MAINSCENE_H

#include "openglmain.h"

#include "camera.h"

#include <memory>
#include <functional>
#include "mesh.h"
#include "../mesh/demoBSpline.hpp"


/** Simple drawing demonstration
 */
class MainScene : public OpenGLMain {
public:
    explicit MainScene(int width, int height);
    ~MainScene() override;

    void resize(int width, int height) override;
    void draw() override;

    void mouseclick(int button, float xpos, float ypos) override;
    void mousemove(float xpos, float ypos) override;
    void keyboardmove(int key, double time) override;
    bool keyboard(unsigned char k) override;

private:

    // Shader program for rendering
    GLuint _program;

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

    DemoBSpline _demobspline;
};

/*------------------------------------------------------------------------------------------------------------------------*/


#endif // MAINSCENE_H
