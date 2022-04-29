#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H


#include <GL/glew.h>
#include "vertexbuffer.h"

class VertexBufferLayout;

class VertexArray
{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void init();
    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer& vb, VertexBufferLayout& layout);
};

#endif // VERTEXARRAY_H
