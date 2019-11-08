#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "glm/glm.hpp"
#include <string>

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

#endif // TEXTURE_H_
