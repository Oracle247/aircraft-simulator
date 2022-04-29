#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H


class IndexBuffer
{
public:
    IndexBuffer();
    IndexBuffer(unsigned int *, unsigned int);
    ~IndexBuffer();

    void init(unsigned int*, unsigned int);
    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const {return m_Count;}
private:
    unsigned int m_Count;
    unsigned int m_rendererID;
};
#endif // INDEXBUFFER_H
