#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include "Vertex.hpp"
#include "Texture.hpp"
#include "../openGL/Shader.hpp"
#include "../openGL/DrawParameter.hpp"


class Mesh {
public:
    /*  Mesh Data  */
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    /*  Functions  */
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(const DrawParameter & para);
private:
    /*  Render data  */
    unsigned int _vao, _vbo, _ebo;
    /*  Functions    */
    void setupMesh();
};


#endif // MESH_H_
