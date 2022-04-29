#ifndef VERTEX_H
#define VERTEX_H

#include "vendor/glm/glm.hpp"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

struct Vertex1{
    glm::vec3 position;
};

#endif // VERTEX_H
