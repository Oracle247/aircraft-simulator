#include "shader.h"
#include "renderer.h"

Shader::Shader(const string filepath)
    : m_Filepath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = parseShader(filepath);
    m_RendererID = createShader(source.VertexSource, source.FragmentSource, source.GeometrySource);
    GLCall(glUseProgram(m_RendererID));

}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}


Shader::ShaderProgramSource Shader::parseShader(const string& filepath)
{
    ifstream stream(filepath);

    enum class ShaderType{
        NONE = -1, VERTEX = 0, FRAGMENT = 1, GEOMETRY = 2
    };

    string line;
    stringstream ss[3];
    ShaderType type = ShaderType::NONE;
    while(getline(stream, line)){
        if(line.find("#shader") != string::npos){
            if(line.find("vertex") != string::npos){
                type = ShaderType::VERTEX;
            }
            else if(line.find("fragment") != string::npos){
                type = ShaderType::FRAGMENT;
            }
            else if(line.find("geometry") != string::npos){
                type = ShaderType::GEOMETRY;
            }
        }
        else{
            ss[(int)type]<<line<<"\n";
        }
    }
    return {ss[0].str(), ss[1].str(), ss[2].str()};
}

GLuint Shader::CompileShader(unsigned int type, const string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if(result == GL_FALSE){
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        cout<<"failed to campile"<<
              (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader")
           <<endl;
        cout<<message<<endl;
        GLCall(glDeleteShader(id));

        return 0;
    }
    return id;

}

unsigned int Shader::createShader(const string& vertexShader, const string& fragmentShader, const string& geometryShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    unsigned int gs = CompileShader(GL_GEOMETRY_SHADER, geometryShader);

    //cout<<"vs = "<<vs<<endl<<"fs = "<<fs<<endl;
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    //GLCall(glAttachShader(program, gs));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));
    //GLCall(glDeleteShader(gs));

    return program;
}
void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

void Shader::SetUniform1i(const string &name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const string &name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform3f(const string &name, const glm::vec3& data)
{
    GLCall(glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(data)));
}

void Shader::SetUniform4f(const string &name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformMat4f(const string &name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
}

unsigned int Shader::GetUniformLocation(const string &name)
{
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if(location == -1){
        cout<<"warning: uniform"<<name<<"doesn't exist"<<endl;
    }
    return location;
}
