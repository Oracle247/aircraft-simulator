#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "renderer.h"
#include "vertex.h"
#include "objloader.h"

#include <random>
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

#include<vector>

class Primitive
{
private:
    std::vector<Vertex> vertices;
    std::vector<Vertex1> vertices1;
    std::vector<GLuint> indices;


public:
    bool position;
    bool color;
    bool texture;
    bool normal;
    unsigned long sizeOfVer;
    unsigned long sizeOfInd;
    Primitive() {}
    virtual ~Primitive() {}

    //Functions
    void set(const Vertex* vertices,
        const unsigned nrOfVertices,
        const GLuint* indices,
        const unsigned nrOfIndices,
        const unsigned long& sizeOfVer,
        const unsigned long& sizeOfInd)
    {
        this->sizeOfVer = sizeOfVer;
        this->sizeOfInd = sizeOfInd;
        for (size_t i = 0; i < nrOfVertices; i++)
        {
            this->vertices.push_back(vertices[i]);
        }

        for (size_t i = 0; i < nrOfIndices; i++)
        {
            this->indices.push_back(indices[i]);
        }
         std::cout<<"size = "<<this->sizeOfVer<<endl;
    }

    void set(vector<Vertex> vertices,
        const unsigned nrOfVertices,
        const GLuint* indices,
        const unsigned nrOfIndices,
        const unsigned long& sizeOfVer,
        const unsigned long& sizeOfInd)
    {
        this->sizeOfVer = sizeOfVer;
        this->sizeOfInd = sizeOfInd;
        for (size_t i = 0; i < nrOfVertices; i++)
        {
            this->vertices.push_back(vertices[i]);
        }

        for (size_t i = 0; i < nrOfIndices; i++)
        {
            this->indices.push_back(indices[i]);
        }
         std::cout<<"size = "<<this->sizeOfVer<<endl;
    }

    inline Vertex* getVertices() {  return this->vertices.data(); }
    inline Vertex1* getVertices1() {  return this->vertices1.data(); }
    inline GLuint* getIndices() { return this->indices.data(); }
    inline unsigned getSizeOfVer(){ return this->sizeOfVer; }
    inline unsigned getSizeOfInd(){ return sizeOfInd; }
    inline unsigned getNrOfVertices() { return this->vertices.size(); }
    inline unsigned getNrOfIndices() { return this->indices.size(); }
    inline bool hasPosition() { return this->position; }
    inline bool hasColor() { return this->color; }
    inline bool hasTexture() { return this->texture; }
    inline bool hasNormal() { return this->normal; }
};

class Triangle : public Primitive
{
public:
    Triangle()
        : Primitive()
    {
        Vertex vertices[] =
        {
            //Position								//Color							//Texcoords					//Normals
            glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(-0.5f, -0.5f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.5f, -0.5f, 0.f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
        unsigned long sizeOfVer = sizeof (vertices);

        GLuint indices[] =
        {
            0, 1, 2	//Triangle 1
        };
        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
        unsigned long sizeOfInd = sizeof (indices);

        //set conditions
        this->position = true;
        this->color = true;
        this->texture = true;
        this->normal = true;

        this->set(vertices, nrOfVertices, indices, nrOfIndices, sizeOfVer, sizeOfInd);
    }
};

class Quad : public Primitive
{
public:
    Quad()
        : Primitive()
    {
        Vertex vertices[] =
        {
            //Position								//Color							//Texcoords					//Normals
            glm::vec3(0.f, 0.f, 0.f) ,			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.5f, 0.f, 0.f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.5f, 0.5f, 0.f),             glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.f, 0.5f, 0.f),            glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
        unsigned long sizeOfVer = sizeof (vertices);

        GLuint indices[] =
        {
            0, 1, 2,	//Triangle 1
            0, 2, 3		//Triangle 2
        };
        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
        unsigned long sizeOfInd = sizeof (indices);

        //set conditions
        this->position = true;
        this->color = true;
        this->texture = true;
        this->normal = true;

        this->set(vertices, nrOfVertices, indices, nrOfIndices, sizeOfVer, sizeOfInd);
    }
};

class Pyramid : public Primitive
{
public:
    Pyramid()
        : Primitive()
    {
        Vertex vertices[] =
        {
            //Position								//Color							//Texcoords					//Normals
            //Triangle front
            glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
            glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),

            //Triangle left
            glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
            glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
            glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),

            //Triangle back
            glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(0.f, 0.f, -1.f),
            glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
            glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),

            //Triangles right
            glm::vec3(0.f, 0.5f, 0.f),				glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.5f, 1.f),		glm::vec3(-1.f, 0.f, 0.f),
            glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
            glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f),
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
        unsigned long sizeOfVer = sizeof (vertices);
        unsigned long sizeOfInd = 0;

        //set conditions
        this->position = true;
        this->color = true;
        this->texture = true;
        this->normal = true;

        this->set(vertices, nrOfVertices, nullptr, 0, sizeOfVer, sizeOfInd);
    }
};

class Cube : public Primitive
{
public:
    Cube()
        : Primitive()
    {

//        {
//            //Position								//Color							//Texcoords					//Normals
//            glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
//            glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
//            glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
//            glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),
//            glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f),
//            glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f),

//            glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),

//            glm::vec3(-0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f),
//            glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f),

//        };
        Vertex vertices[] =
        {
            //Position								//Color							//Texcoords					//Normals
            //front face
            {glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)},
            {glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, 1.f)},
            {glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f)},
            {glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)},
            {glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, 1.f)},
            {glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, 1.f)},

            //left face
            {glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f)},
            {glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f)},
            {glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f)},
            {glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f)},
            {glm::vec3(-0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(-1.f, 0.f, 0.f)},
            {glm::vec3(-0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(-1.f, 0.f, 0.f)},

            //back face
            {glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f)},
            {glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, 0.f, -1.f)},
            {glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f)},
            {glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 0.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, 0.f, -1.f)},
            {glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(0.f, 0.f, 1.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, 0.f, -1.f)},
            {glm::vec3(-0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, 0.f, -1.f)},

            //right face
            {glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(1.f, 0.f, 0.f)},
            {glm::vec3(0.5f, -0.5f, 0.5f),			glm::vec3(0.f, 0.f, 1.f),		glm::vec2(0.f, 0.f),		glm::vec3(1.f, 0.f, 0.f)},
            {glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f)},
            {glm::vec3(0.5f, 0.5f, 0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(1.f, 0.f, 0.f)},
            {glm::vec3(0.5f, -0.5f, -0.5f),			glm::vec3(0.f, 1.f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(1.f, 0.f, 0.f)},
            {glm::vec3(0.5f, 0.5f, -0.5f),			glm::vec3(1.f, 1.f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(1.f, 0.f, 0.f)}
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
        unsigned long sizeOfVer = sizeof (vertices);

//        GLuint indices[] =
//        {
//            0, 1, 2,
//            0, 2, 3,

//            7, 6, 1,
//            7, 1, 0,

//            4, 5, 6,
//            4, 6, 7,

//            3, 2, 5,
//            3, 5, 4
//        };
//        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
//        unsigned long sizeOfInd = sizeof (indices);

        unsigned long sizeOfInd = 0;

        //set conditions
        this->position = true;
        this->color = true;
        this->texture = true;
        this->normal = true;

        this->set(vertices, nrOfVertices, nullptr, 0, sizeOfVer, sizeOfInd);
    }
};

class SkyBox : public Primitive
{
public:
    SkyBox()
        : Primitive()
    {

        Vertex vertices[] = {
            // positions
            {glm::vec3(-1.0f,  1.0f, -1.0f)},
            {glm::vec3(-1.0f, -1.0f, -1.0f)},
            {glm::vec3( 1.0f, -1.0f, -1.0f)},
            {glm::vec3( 1.0f, -1.0f, -1.0f)},
            {glm::vec3( 1.0f,  1.0f, -1.0f)},
            {glm::vec3(-1.0f,  1.0f, -1.0f)},

            {glm::vec3(-1.0f, -1.0f,  1.0f)},
            {glm::vec3(-1.0f, -1.0f, -1.0f)},
            {glm::vec3(-1.0f,  1.0f, -1.0f)},
            {glm::vec3(-1.0f,  1.0f, -1.0f)},
            {glm::vec3(-1.0f,  1.0f,  1.0f)},
            {glm::vec3(-1.0f, -1.0f,  1.0f)},

            {glm::vec3( 1.0f, -1.0f, -1.0f)},
            {glm::vec3( 1.0f, -1.0f,  1.0f)},
            {glm::vec3( 1.0f,  1.0f,  1.0f)},
            {glm::vec3( 1.0f,  1.0f,  1.0f)},
            {glm::vec3( 1.0f,  1.0f, -1.0f)},
            {glm::vec3( 1.0f, -1.0f, -1.0f)},

            {glm::vec3(-1.0f, -1.0f,  1.0f)},
            {glm::vec3(-1.0f,  1.0f,  1.0f)},
            {glm::vec3( 1.0f,  1.0f,  1.0f)},
            {glm::vec3( 1.0f,  1.0f,  1.0f)},
            {glm::vec3( 1.0f, -1.0f,  1.0f)},
            {glm::vec3(-1.0f, -1.0f,  1.0f)},

            {glm::vec3(-1.0f,  1.0f, -1.0f)},
            {glm::vec3( 1.0f,  1.0f, -1.0f)},
            {glm::vec3( 1.0f,  1.0f,  1.0f)},
            {glm::vec3( 1.0f,  1.0f,  1.0f)},
            {glm::vec3(-1.0f,  1.0f,  1.0f)},
            {glm::vec3(-1.0f,  1.0f, -1.0f)},

            {glm::vec3(-1.0f, -1.0f, -1.0f)},
            {glm::vec3(-1.0f, -1.0f,  1.0f)},
            {glm::vec3( 1.0f, -1.0f, -1.0f)},
            {glm::vec3( 1.0f, -1.0f, -1.0f)},
            {glm::vec3(-1.0f, -1.0f,  1.0f)},
            {glm::vec3( 1.0f, -1.0f,  1.0f)}
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
        unsigned long sizeOfVer = sizeof (vertices);

        unsigned long sizeOfInd = 0;

        //set conditions
        this->position = true;
        this->color = true;
        this->texture = true;
        this->normal = true;

        this->set(vertices, nrOfVertices, nullptr, 0, sizeOfVer, sizeOfInd);
    }
};

class Terrain : public Primitive
{
public:
    Terrain()
        : Primitive()
    {
        Vertex vertices[] = {
            //Position								//Color							//Texcoords					//Normals
            glm::vec3(-6.f, -1.f, 2.f),         glm::vec3(0.f, 0.3f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
            glm::vec3(6.f, -1.f, 2.f),			glm::vec3(0.f, 0.3f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
            glm::vec3(6.0f, -1.f, -10.f),       glm::vec3(0.f, 0.3f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),
            glm::vec3(-6.0f, -1.f, -10.f),		glm::vec3(0.f, 0.3f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, -1.f, 0.f)
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
        unsigned long sizeOfVer = sizeof (vertices);

        GLuint indices[] = {
            0, 1, 2,
            0, 2, 3
        };
        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
        unsigned long sizeOfInd = sizeof (indices);

        //set conditions
        this->position = true;
        this->color = true;
        this->texture = true;
        this->normal = true;

        this->set(vertices, nrOfVertices, indices, nrOfIndices, sizeOfVer, sizeOfInd);
    }
};


class Terrain2 : public Primitive
{
public:
    Terrain2()
        : Primitive()
    {
        Vertex vertices[] = {
            //Position								//Color							//Texcoords					//Normals
            glm::vec3(-60.f, -1.01f, 20.f),         glm::vec3(0.f, 0.3f, 0.f),		glm::vec2(0.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
            glm::vec3(60.f, -1.01f, 20.f),		  glm::vec3(0.f, 0.3f, 0.f),		glm::vec2(1.f, 0.f),		glm::vec3(0.f, -1.f, 0.f),
            glm::vec3(60.0f, -1.01f, -100.f),       glm::vec3(0.f, 0.3f, 0.f),		glm::vec2(1.f, 1.f),		glm::vec3(0.f, -1.f, 0.f),
            glm::vec3(-60.0f, -1.01f, -100.f),	  glm::vec3(0.f, 0.3f, 0.f),		glm::vec2(0.f, 1.f),		glm::vec3(0.f, -1.f, 0.f)
        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
        unsigned long sizeOfVer = sizeof (vertices);

        GLuint indices[] = {
            0, 1, 2,
            0, 2, 3
        };
        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
        unsigned long sizeOfInd = sizeof (indices);

        //set conditions
        this->position = true;
        this->color = true;
        this->texture = true;
        this->normal = true;

        this->set(vertices, nrOfVertices, indices, nrOfIndices, sizeOfVer, sizeOfInd);
    }
};

class Plane : public Primitive
{
public:
    Plane()
        : Primitive()
    {
        Vertex vertices[] = {
            // positions
            {glm::vec3(-0.1f, 0.0f, -0.5f)},
            {glm::vec3(-0.1f, 0.0f, 0.5f)},
            {glm::vec3( 0.1f, 0.0f, 0.5f)},
            {glm::vec3( 0.1f, 0.0f, -0.5f)},

            {glm::vec3(-0.1f, 0.0f,  0.0f)},
            {glm::vec3(-0.3f, 0.0f, -0.3f)},
            {glm::vec3(-0.1f, 0.0f, -0.32f)},

            {glm::vec3(0.1f, 0.0f,  0.0f)},
            {glm::vec3(0.3f, 0.0f, -0.3f)},
            {glm::vec3(0.1f, 0.0f, -0.32f)},



        };
        unsigned nrOfVertices = sizeof(vertices) / sizeof(Vertex);
        unsigned long sizeOfVer = sizeof (vertices);
        GLuint indices[] = {
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            7, 8, 9
        };

        unsigned nrOfIndices = sizeof(indices) / sizeof(GLuint);
        unsigned long sizeOfInd = sizeof (indices);

//        unsigned long sizeOfInd = 0;

        //set conditions
        this->position = true;
        this->color = true;
        this->texture = true;
        this->normal = true;

        this->set(vertices, nrOfVertices, indices, nrOfIndices, sizeOfVer, sizeOfInd);
    }
};

class Heightmap : public Primitive
{
public:
    struct HillAlgorithmParameters
    {
        HillAlgorithmParameters(int rows, int columns, int numHills, int hillRadiusMin, int hillRadiusMax, float hillMinHeight, float hillMaxHeight)
        {
            this->rows = rows;
            this->columns = columns;
            this->numHills = numHills;
            this->hillRadiusMin = hillRadiusMin;
            this->hillRadiusMax = hillRadiusMax;
            this->hillMinHeight = hillMinHeight;
            this->hillMaxHeight = hillMaxHeight;
        }

        int rows;
        int columns;
        int numHills;
        int hillRadiusMin;
        int hillRadiusMax;
        float hillMinHeight;
        float hillMaxHeight;
    };

    Heightmap(const HillAlgorithmParameters& params, bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true);

    void createFromHeightData(const std::vector<float> &heightData);

    void render() const;
    void renderPoints() const;

    int getRows() const;
    int getColumns() const;
    float getHeight(const int row, const int column) const;

    static std::vector<glm::vec3> generateRandomHeightData(const HillAlgorithmParameters& params);

    //random_device rd;

private:
    void setUpVertices();
    void setUpTextureCoordinates();
    void setUpNormals();
    void setUpIndexBuffer();

    std::vector<glm::vec3> m_heightData;
    std::vector<glm::vec3> m_vertices;
    std::vector<glm::vec2> m_extureCoordinates;
    std::vector<glm::vec3> m_normals;
    int _rows = 0;
    int _columns = 0;
};

#endif // PRIMITIVE_H

//std::vector<glm::vec3> Heightmap::generateRandomHeightData(const HillAlgorithmParameters& params)
//{
//	std::vector<double> heightData(params.rows, std::vector<double>(params.columns, 0.0f));

//	std::random_device rd;
//	std::mt19937 generator(rd());
//	std::uniform_int_distribution hillRadiusDistribution(params.hillRadiusMin, params.hillRadiusMax);
//	std::uniform_real_distribution hillHeightDistribution(params.hillMinHeight, params.hillMaxHeight);
//	std::uniform_int_distribution hillCenterRowIntDistribution(0, params.rows - 1);
//	std::uniform_int_distribution hillCenterColIntDistribution(0, params.columns - 1);

//	for (int i = 0; i < params.numHills; i++)
//	{
//		const auto hillCenterRow = hillCenterRowIntDistribution(generator);
//		const auto hillCenterCol = hillCenterColIntDistribution(generator);
//		const auto hillRadius = hillRadiusDistribution(generator);
//		const auto hillHeight = hillHeightDistribution(generator);

//		for (auto r = hillCenterRow - hillRadius; r < hillCenterRow + hillRadius; r++)
//		{
//			for (auto c = hillCenterCol - hillRadius; c < hillCenterCol + hillRadius; c++)
//			{
//				if (r < 0 || r >= params.rows || c < 0 || c >= params.columns) {
//					continue;
//				}
//				const auto r2 = hillRadius * hillRadius; // r*r term
//				const auto x2x1 = hillCenterCol - c; // (x2-x1) term
//				const auto y2y1 = hillCenterRow - r; // (y2-y1) term
//				const auto height = float(r2 - x2x1 * x2x1 - y2y1 * y2y1);
//				if (height < 0.0f) {
//					continue;
//				}
//				const auto factor = height / r2;
//				heightData[r][c] += hillHeight * factor;
//				if (heightData[r][c] > 1.0f) {
//					heightData[r][c] = 1.0f;
//				}
//			}
//		}
//	}
//	return heightData;
//}
