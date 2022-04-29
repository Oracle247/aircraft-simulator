#ifndef MATERIAL_H
#define MATERIAL_H
#include "renderer.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"

using namespace glm;

class Material{
private:
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;

public:
    Material(
    vec3 ambient,
    vec3 diffuse,
    vec3 specular,
    float shininess
    ){
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
    };

    void sendToShader(Shader &shader) {
        shader.SetUniform3f("ambient", this->ambient);
        shader.SetUniform3f("diffuse", this->diffuse);
//        shader.SetUniform3f("material.specular", this->specular);
//        shader.SetUniform1f("material.shininess", this->shininess);
    }
};

#endif // MATERIAL_H
