#include "mesh.h"


void Mesh::updateUniforms(Shader& shader)
{
    shader.SetUniformMat4f("model", m_Model);
}

void Mesh::updateModelMatrix()
{
    m_Model = mat4(1.f);
    //this->origin = this->position;
    //m_Model = translate(m_Model, this->position);
    vec3 dummy = this->position;
    //m_Model = translate(m_Model, vec3(0.f, 0.f, 0.f));
    m_Model = rotate(m_Model, radians(this->rotation.x), vec3(1.f, 0.f, 0.f));
    m_Model = rotate(m_Model, radians(this->rotation.y), vec3(0.f, 1.f, 0.f));
    m_Model = rotate(m_Model, radians(this->rotation.z), vec3(0.f, 0.f, 1.f));
    m_Model = translate(m_Model, this->position /*- this->origin*/);
    m_Model = glm::scale(m_Model, this->scale);

    //this->origin = this->position;
}

Mesh::Mesh(Vertex *vertexArray, const unsigned int &nrOfVertices, unsigned int *indexArray, const unsigned &nrOfIndices, vec3 position, vec3 origin, vec3 rotation, vec3 scale) :
    position{glm::vec3(0.f)},
    origin {glm::vec3(0.f)},
    rotation {glm::vec3(0.f)},
    scale {glm::vec3(1.f)}

{
    this->m_nrOfVertices = nrOfVertices;
    this->m_nrOfIndices = nrOfIndices;
    //m_vertices = vertexArray;
    this->m_vertexArray = new Vertex[this->m_nrOfVertices];
    for (size_t i = 0; i < nrOfVertices; i++)
    {
        this->m_vertexArray[i] = vertexArray[i];
    }

    m_indexArray = new GLuint[this->m_nrOfIndices];
    for (size_t i = 0; i < nrOfIndices; i++)
    {
        m_indexArray[i] = indexArray[i];
    }

    this->initVAO();
    this->updateModelMatrix();
}

Mesh::Mesh(VertexArray& va, VertexBuffer& vb, IndexBuffer& ib, VertexBufferLayout& layout, Vertex *vertexArray, const unsigned int& nrOfVertices, unsigned int *indexArray, const unsigned int& nrOfIndices) :
    position{glm::vec3(0.f)},
    origin {glm::vec3(0.f)},
    rotation {glm::vec3(0.f)},
    scale {glm::vec3(1.f)} 

{
    m_nrOfVertices = nrOfVertices;
    m_nrOfIndices = nrOfIndices;

    m_vertexArray = new Vertex[m_nrOfVertices];
    for (size_t i = 0; i < nrOfVertices; i++)
    {
        m_vertexArray[i] = vertexArray[i];
    }

    m_indexArray = new GLuint[m_nrOfIndices];
    for (size_t i = 0; i < nrOfIndices; i++)
    {
        m_indexArray[i] = indexArray[i];
    }

    this->initVAO();
}

Mesh::Mesh(Primitive primitive, vec3 position, vec3 origin, vec3 rotation, vec3 scale)
{
    this->position = position;
    this->origin = origin;
    this->rotation = rotation;
    this->scale = scale;
    this->rot = false;
    this->trans = false;

    m_sizeOfVer = primitive.getSizeOfVer();
    m_nrOfVertices = primitive.getNrOfVertices();
    m_nrOfIndices = primitive.getNrOfIndices();

    m_vertexArray = new Vertex[m_nrOfVertices];
    for (size_t i = 0; i < m_nrOfVertices; i++)
    {
        m_vertexArray[i] = primitive.getVertices()[i];
    }

    m_indexArray = new GLuint[m_nrOfIndices];
    for (size_t i = 0; i < m_nrOfIndices; i++)
    {
        m_indexArray[i] = primitive.getIndices()[i];
    }

    this->initVAO();
}

Mesh::Mesh(OBJLoader obj, vec3 position, vec3 origin, vec3 rotation, vec3 scale)
{
    this->position = position;
    this->origin = origin;
    this->rotation = rotation;
    this->scale = scale;

    m_sizeOfVer = obj.getSizeOfVer();
    m_nrOfVertices = obj.getNrOfVertices();
    m_nrOfIndices = obj.getNrOfIndices();

    m_vertexArray = new Vertex[m_nrOfVertices];
    for (size_t i = 0; i < m_nrOfVertices; i++)
    {
        m_vertexArray[i] = obj.getVertices()[i];
    }

    m_indexArray = new GLuint[m_nrOfIndices];
    for (size_t i = 0; i < m_nrOfIndices; i++)
    {
        m_indexArray[i] = obj.getIndices()[i];
    }

    this->initVAO();
}

void Mesh::initVao(VertexArray &va, VertexBuffer &vb, IndexBuffer &ib, VertexBufferLayout &layout)
{

    va.init();
    vb.init(m_vertexArray, m_sizeOfVer, m_nrOfVertices);
    ib.init(m_indexArray, m_nrOfIndices);

    //position attribute
    layout.push<float>(3);
    //color attribute
    layout.push<float>(3);
    //texture attribute
    layout.push<float>(2);
    //normal attribute
    layout.push<float>(3);

    va.AddBuffer(vb, layout);
}

void Mesh::makeOrigin(const vec3 position)
{
    setOrigin(position);
//    m_Model = mat4();
//    m_Model = translate(m_Model, vec3)
}


void Mesh::setPosition(const vec3 position)
{
    this->position = position;
}

void Mesh::setOrigin(const vec3 origin)
{
    this->origin = origin;
}

void Mesh::setRotation(const vec3 rotation)
{
    this->rotation = rotation;
}

void Mesh::setScale(const vec3 setScale)
{
    this->scale = setScale;
}

mat4 Mesh::getModelMatrix()
{
    return this->m_Model;
}

vec3 Mesh::getPostion()
{
    return this->position;
}

void Mesh::move(const float position, bool trans)
{
    this->trans = trans;
    this->position.z += position;
}

void Mesh::Rotate(const vec3 rotation, bool rot)
{
    this->rot = rot;
    this->rotation += rotation;
}

void Mesh::scaleUp(const vec3 scale)
{
    this->scale += scale;
}

void Mesh::update()
{

}

void Mesh::initVAO()
{
    va.init();
    this->vb.init(m_vertexArray, m_sizeOfVer, m_nrOfVertices);
    this->ib.init(m_indexArray, m_nrOfIndices);

    //position attribute
    this->layout.push<float>(3);

    //color attribute
    this->layout.push<float>(3);
    //texture attribute
    layout.push<float>(2);
    //normal attribute
    layout.push<float>(3);
    va.AddBuffer(vb, layout);
}



void Mesh::Unbind(Shader& shader) const
{
    shader.Unbind();
    vb.Unbind();
    va.Unbind();
    ib.Unbind();
}

void Mesh::Draw(Shader& shader)
{
    this->updateModelMatrix();   
    shader.Bind();
    this->updateUniforms(shader);
    vb.Bind();
    va.Bind();
    ib.Bind();
    if(ib.GetCount() == 0){
        GLCall(glDrawArrays(GL_TRIANGLES, 0, 32));
    }
    else{
        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
}

