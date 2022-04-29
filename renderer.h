#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include "indexbuffer.h"
#include "vertexarray.h"
#include "shader.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#define ASSERT(x) if(!(x)) __builtin_trap();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))


void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class Render{
public:
    void Draw(const VertexArray&, const VertexBuffer&, const IndexBuffer&, const Shader&) const;
};

#endif // RENDERER_H
