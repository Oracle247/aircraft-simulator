#ifndef OBJLOADER_H
#define OBJLOADER_H

//STD Libs
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<algorithm>

#include "renderer.h"
#include "vertex.h"

using namespace std;

class OBJLoader{

public:
    vector<Vertex> vertices;
    vector<GLint> indice;
    unsigned long sizeOfVer;
    unsigned long sizeOfInd;
    OBJLoader(){ }
    ~OBJLoader(){ }

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
            this->indice.push_back(indices[i]);
        }
         //std::cout<<"size = "<<this->sizeOfVer<<endl;
    }

    vector<Vertex> loadOBJ(const char *filename, unsigned long& nrOfVer, unsigned long& sizeOfVer){
        vector<Vertex> vertices;
        //vertex
        vector<glm::vec3> vertex_positions;
        vector<glm::vec2> vertex_texcoords;
        vector<glm::vec3> vertex_normals;

        //face vector
        vector<unsigned int> vertex_pos_indicies;
        vector<unsigned int> vertex_tex_indicies;
        vector<unsigned int> vertex_norm_indicies;

        //filename = filename;
        stringstream ss;
        ifstream in_file(filename);
        string line = "";
        string prefix = "";
        glm::vec3 temp_vec3;
        glm::vec2 temp_vec2;
        GLint temp_glint = 0;

        //file open error check
        if(!in_file.is_open()){
            throw "ERROR::OBJLOADER::Could not open file";
        }

        //read one line at a time
        while (std::getline(in_file, line)) {
            //get the prefix of the line
            ss.clear();
            ss.str(line);
            ss >> prefix;

            if (prefix == "#")
            {

            }
            else if (prefix == "o")
            {

            }
            else if (prefix == "s")
            {

            }
            else if (prefix == "use_mtl")
            {

            }
            else if (prefix == "v") //Vertex position
            {
                ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
                vertex_positions.push_back(temp_vec3);
            }
            else if (prefix == "vt")
            {
                ss >> temp_vec2.x >> temp_vec2.y;
                //std::cout<<"x = " << temp_vec2.x << "y = " <<temp_vec2.y<<endl;
                vertex_texcoords.push_back(temp_vec2);
            }
            else if (prefix == "vn")
            {
                ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
                vertex_normals.push_back(temp_vec3);
            }
            else if (prefix == "f"){
                int counter = 0;
                while (ss >> temp_glint){
                    //pushing indices into correct arrays
                    if (counter == 0)
                        vertex_pos_indicies.push_back(temp_glint);
                    else if (counter == 1)
                        vertex_tex_indicies.push_back(temp_glint);
                    else if (counter == 2)
                        vertex_norm_indicies.push_back(temp_glint);

                    //Handling characters
                    if (ss.peek() == '/')
                    {
                        ++counter;
                        ss.ignore(1, '/');
                    }
                    else if (ss.peek() == ' ')
                    {
                        ++counter;
                        ss.ignore(1, ' ');
                    }

                    //Reset the counter
                    if (counter > 2)
                        counter = 0;
                }
            }

            else
                {

                }

        }

        //Build final vertex array (mesh)
        vertices.resize(vertex_pos_indicies.size(), Vertex());

        //Load in all indices
        for (size_t i = 0; i < vertices.size(); i++)
        {
            vertices[i].position = vertex_positions[vertex_pos_indicies[i] - 1];
            vertices[i].texcoord = vertex_texcoords[vertex_tex_indicies[i] - 1];
            vertices[i].normal = vertex_normals[vertex_norm_indicies[i] - 1];
            vertices[i].color = glm::vec3(1.f, 1.f, 1.f);
        }

        //compute vertices stuff
        nrOfVer = vertices.size();
        sizeOfVer = sizeof (vertices) * sizeof (Vertex);

        //DEBUG
        std::cout << "Nr of vertices: " << vertices.size() << "\n";
        //std::cout << "data of vertices: " << sizeof(vertices) << endl;

        //Loaded success
        std::cout << "OBJ file loaded!" << "\n";
        return vertices;
    }

    inline Vertex* getVertices() {  return this->vertices.data(); }
    inline GLuint* getIndices() { return 0; }
    inline unsigned getSizeOfVer(){ return this->sizeOfVer; }
    inline unsigned getSizeOfInd(){ return sizeOfInd; }
    inline unsigned getNrOfVertices() { return this->vertices.size(); }
    inline unsigned getNrOfIndices() { return this->indice.size(); }


};

class OBJ : public OBJLoader{
public:
    OBJ() : OBJLoader(){
        vector<Vertex> vertices;
        unsigned long nrOfVer;
        unsigned long sizeOfVer;

        vertices = loadOBJ("/home/eresoft/Desktop/Oracle247/my progs/Qt-projects/Aircraft_simulator/res/model/cross.obj", nrOfVer, sizeOfVer);
        unsigned long sizeOfInd = 0;
        set(vertices, nrOfVer, nullptr, 0, sizeOfVer, sizeOfInd);
};

};

#endif // OBJLOADER_H
