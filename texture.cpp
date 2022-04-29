#include "texture.h"
#include "vendor/stb_image/stb_image.h"

Texture::Texture(const string path)
    : m_RendererID(0), m_Filepath(path), m_LocalBuffer(nullptr),
      m_Width(0), m_Height(0), m_BPP(0)
{
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    GLenum internalFormat = 0;
    GLenum format = 0;
    if(m_BPP == 4){
        internalFormat = format = GL_RGBA;
    }
    else if(m_BPP == 3){
        internalFormat = format = GL_RGB;
    }
    else if(m_BPP == 2){
        internalFormat = format = GL_ALPHA;
    }

    if(m_LocalBuffer){
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer));
        GLCall(glGenerateMipmap(GL_TEXTURE_2D));
    }
    else{
        cout << "Failed to load textu7re" << endl;
    }
//    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    if(m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);

}

Texture::Texture(vector<string> paths)
    : m_RendererID(0), m_LocalBuffer(nullptr),
      m_Width(0), m_Height(0), m_BPP(0)
{
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID));

    stbi_set_flip_vertically_on_load(0);

    for(size_t i = 0; i < paths.size(); i++){

        m_LocalBuffer = stbi_load(paths[i].c_str(), &m_Width, &m_Height, &m_BPP, 0);

        GLenum internalFormat = 0;
        GLenum format = 0;
        if(m_BPP == 4){
            internalFormat = format = GL_RGBA;
        }
        else if(m_BPP == 3){
            internalFormat = format = GL_RGB;
        }
        else if(m_BPP == 2){
            internalFormat = format = GL_ALPHA;
        }

        if(m_LocalBuffer){
            GLCall(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer));
            //GLCall(glGenerateMipmap(GL_TEXTURE_2D));
            stbi_image_free(m_LocalBuffer);
        }
        else{
            cout << "Failed to load textu7re" << endl;
            stbi_image_free(m_LocalBuffer);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}



Texture::~Texture()
{
    GLCall(glDeleteTextures(1, &m_RendererID))
}

void Texture::Bind(unsigned int slot) const
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
