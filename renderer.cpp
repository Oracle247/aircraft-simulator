#include "renderer.h"

#include <iostream>

using namespace std;

void GLClearError()
{
    while(glGetError() != GL_NO_ERROR);
}


bool GLLogCall(const char *function, const char *file, int line)
{
    while(GLenum error = glGetError()){
        cout<<"[OpenGL Error] ("<<error<<"): "<<function<<" "<<file<<":"<<line<<endl;
        return false;
    }
    return true;
}

void Render::Draw(const VertexArray& va, const VertexBuffer& vb, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    vb.Bind();
    va.Bind();
    ib.Bind();
    if(ib.GetCount() == 0){
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
    }
    else{
        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
}
