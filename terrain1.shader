#shader vertex
#version 440 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 normal;

out vec4 v_color;
out vec3 v_position;
out vec2 v_texcoord;
out vec3 v_normal;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(position, 1.0f);

    v_position = vec4(model * vec4(position, 1.0f)).xyz;
    v_normal = mat3(model) * normal;
    v_color = vec4(color, 1.0f);
    v_texcoord = texture;
}

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec3 v_position;
in vec4 v_color;
in vec2 v_texcoord;
in vec3 v_normal;

uniform vec4 u_color;
uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform vec3 lightPos0;
uniform vec3 camPosition1;

//struct Material {
//    vec3 ambient;
//    vec3 diffuse;
//    vec3 specular;
//    float shininess;
//};

uniform vec3 u_ambient;
uniform vec3 u_diffuse;

//uniform Material material;

void main(){
//    color = v_color;
    //ambient light
    vec3 ambientLight = u_ambient;

//    //specular lighting
//    vec3 lightToPosDirVec = normalize(v_position - lightPos0);
//    vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(v_normal)));
//    vec3 posToViewDirVec = normalize(camPosition1 - v_position);
//    float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), material.shininess);
//    vec3 specularFinal = specularConstant * material.specular;

    //diffuse light
    vec3 norm = normalize(v_normal);
    vec3 posToLightDirVec = normalize(v_position - lightPos0 );
    vec3 diffuseColor = vec3(1.f, 1.f, 1.f);
    float diffuseLight = clamp(dot(posToLightDirVec, norm), 0, 1);
    vec3 diffuseFinal =(diffuseLight * u_diffuse);

    vec4 snowTexel = texture2D(u_texture2, v_texcoord/0.2);
    vec4 pathTexel = texture2D(u_texture0, v_texcoord);
    vec4 pavementTexel = texture2D(u_texture1, v_texcoord/0.1);
    float pathWeight = pathTexel.r;
    float snowWeight = 1.0-pathWeight;
    vec4 texColor = pavementTexel * pathWeight + snowTexel * snowWeight;

    vec3 lightColor = ambientLight + diffuseFinal;

    color = texColor * vec4(lightColor, 1.0f);
//    vec4 tex1 = texture2D(u_texture0, v_texcoord);
//    vec4 tex2 = texture2D(u_texture1, v_texcoord);
//    vec4 tex3 = texture2D(u_texture2, v_texcoord);
//    vec4 texColor = tex1 * tex2 * tex3;

//    color =texColor/* * (vec4(ambientLight, 1.f) + vec4(diffuseFinal, 1.0f) + vec4(specularFinal, 1.f))*/;
}


#shader geometry
#version 440 core

int main(){
return 0;
}

