#include <iostream>
#include <vector>
#include "vertexarray.h"
#include "renderer.h"
#include "vertexbufferlayout.h"

using namespace std;

VertexArray::VertexArray()
{

}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::init()
{
    GLCall(glGenVertexArrays(1, &m_RendererID)); // Generate VAO
    std::cout<<m_RendererID<<endl;
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, VertexBufferLayout &layout)
{
    GLCall(vb.Bind());
    vector<unsigned int> offset;
    layout.GetOffset(offset);
    const auto& elements = layout.GetElement();
    for (unsigned int i = 0; i < elements.size(); i++){
        const auto& element = elements[i];
        GLCall(glEnableVertexAttribArray(i));

        GLCall(glVertexAttribPointer(i, element.count, element.type,
                          element.normalized, layout.GetStride(), (const void*)(offset[i])));

    }
}
