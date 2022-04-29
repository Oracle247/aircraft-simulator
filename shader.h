#ifndef SHADER_H
#define SHADER_H


#include<iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

#include "vendor/glm/glm.hpp"
#include"vendor/glm/gtc/type_ptr.hpp"

using namespace std;

class Shader
{
private:
    string m_Filepath;
    unsigned int m_RendererID;
    // caching for uniforms

public:
    struct ShaderProgramSource{
        string VertexSource;
        string FragmentSource;
        string GeometrySource;

    };
    Shader(){}
    Shader(const string filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    //set uniforms
    void SetUniform1i(const string& name, int value);
    void SetUniform1f(const string& name, float value);
    void SetUniform3f(const string &name, const glm::vec3& lightPos);
    void SetUniform4f(const string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const string& name, const glm::mat4& matrix);
private:
    ShaderProgramSource parseShader(const string&);
    unsigned int CompileShader(unsigned int type, const string& source);
    unsigned int createShader(const string&, const string&, const string &geometryShade);

    unsigned int GetUniformLocation(const string& name);
};

#endif // SHADER_H
