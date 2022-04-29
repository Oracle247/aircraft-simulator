#ifndef VERTEXBUFFERLAYOUT_H
#define VERTEXBUFFERLAYOUT_H

#include <GL/glew.h>
#include <vector>
#include "renderer.h"
using namespace std;

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch(type){
            case GL_FLOAT:         return 4;
            case GL_UNSIGNED_INT:  return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        ASSERT(false);
        return 0;
    }
};

class VertexBufferLayout
{
private:
    vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
    unsigned int m_count;
    vector<unsigned int> m_Offset;
    int i;

public:
    VertexBufferLayout()
        : m_Stride(0), m_count(0), i(0) { m_Offset = {0, 0, 0, 0}; }

    template<typename T>
    void push(unsigned int count){
        static_assert(sizeof (T)==0, "failed");
    }

    inline const vector<VertexBufferElement> GetElement() const { return m_Elements; }
    inline unsigned int GetStride() const { return m_Stride; }
    inline vector<unsigned int> GetOffset(vector<unsigned int>& vec) {
        vec = m_Offset;
        return vec;
    }
};


template<>
void inline VertexBufferLayout::push<float>(unsigned int count){
    m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
    m_count += count;
    m_Offset[i + 1] = m_count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    i++;
}

template<>
void inline  VertexBufferLayout::push<unsigned int>(unsigned int count){
    m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}

template<>
void inline VertexBufferLayout::push<unsigned char>(unsigned int count){
    m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
}

#endif // VERTEXBUFFERLAYOUT_H
