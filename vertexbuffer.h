#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H


class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(const void*, unsigned int, unsigned int);
    ~VertexBuffer();

    void init(const void*, unsigned int, unsigned int);
    void Bind() const;
    void Unbind() const;
    inline unsigned int GetCount() const;
private:
    unsigned int m_Count;
    unsigned int m_rendererID;
};


#endif // VERTEXBUFFER_H
