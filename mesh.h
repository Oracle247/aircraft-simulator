#ifndef MESH_H
#define MESH_H

#include "vertex.h"
#include "renderer.h"
#include "vertexbuffer.h"
#include "indexbuffer.h"
#include "vertexbufferlayout.h"
#include "material.h"
#include "primitive.h"
#include "objloader.h"
#include "vector"

using namespace glm;

class Mesh
{
private:
    vector<Vertex> m_vertices;
    Vertex * m_vertexArray;
    Vertex1 * m_vertexArray1;
    unsigned int m_nrOfVertices;
    GLuint* m_indexArray;
    unsigned int m_nrOfIndices;
    unsigned long m_sizeOfVer;

    glm::vec3 position;
    glm::vec3 origin;
    glm::vec3 rotation;
    glm::vec3 scale;

    bool rot;
    bool trans;

    glm::mat4 m_Model;

    void initVAO();
    void updateUniforms(Shader&);
    void updateModelMatrix();
public:
    Mesh(
            Vertex *vertexArray,
            const unsigned int& nrOfVertices,
            unsigned int* indexArray,
            const unsigned& nrOfIndices,
            glm::vec3 position = glm::vec3(0.f),
            glm::vec3 origin = glm::vec3(0.f),
            glm::vec3 rotation = glm::vec3(0.f),
            glm::vec3 scale = glm::vec3(1.f));

    Mesh(VertexArray&, VertexBuffer&, IndexBuffer&, VertexBufferLayout &layout,
            Vertex* vertexArray,
            const unsigned int& nrOfVertices,
            unsigned int* indexArray,
            const unsigned int& nrOfIndices
            );

    Mesh(
            Primitive primitive,
            glm::vec3 position = glm::vec3(0.f),
            glm::vec3 origin = glm::vec3(1.f),
            glm::vec3 rotation = glm::vec3(0.f),
            glm::vec3 scale = glm::vec3(1.f)
            );

    Mesh(
            OBJLoader obj,
            glm::vec3 position = glm::vec3(0.f),
            glm::vec3 origin = glm::vec3(0.f),
            glm::vec3 rotation = glm::vec3(0.f),
            glm::vec3 scale = glm::vec3(1.f));

    VertexArray va;
    VertexBuffer vb;
    IndexBuffer ib;
    VertexBufferLayout layout;
    Shader shader;

    void initVao(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, VertexBufferLayout& layout);

    //Accessors
        //Modifiers
        void makeOrigin(const glm::vec3 postion);
        void setPosition(const glm::vec3 position);
        void setOrigin(const glm::vec3 origin);
        void setRotation(const glm::vec3 rotation);
        void setScale(const glm::vec3 setScale);
        //Functions
        mat4 getModelMatrix();
        vec3 getPostion();
        void move(const float position, bool trans);
        void Rotate(const glm::vec3 rotation, bool rot);
        void scaleUp(const glm::vec3 scale);
        void update();

    void Unbind(Shader&) const;
    void Draw(Shader&);


};

#endif // MESH_H
