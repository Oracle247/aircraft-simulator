#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <vector>
#include "renderer.h"

using namespace std;

class Texture
{
private:
    unsigned int m_RendererID;
    string m_Filepath;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;
public:
    Texture(const string path);
    Texture(vector<string> paths);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const{ return m_Width; }
    inline int GetHeight() const{ return m_Height; }
};

#endif // TEXTURE_H
