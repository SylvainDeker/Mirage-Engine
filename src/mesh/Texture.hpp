#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "glm/glm.hpp"
#include <string>
#include "../openGL/stb_image.h"
#include "../openGL/opengl_stuff.h"

class Texture {
public:
    unsigned int id;
    std::string type;
    std::string path;

    static unsigned int load(char const * path);
};

#endif // TEXTURE_H_
