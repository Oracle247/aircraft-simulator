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
//uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * model * vec4(position, 1.0f);

//    v_position = vec4(model * vec4(position, 1.0f)).xyz;
//    v_normal = mat3(model) * normal;
//    v_color = vec4(color, 1.0f);
    v_texcoord = texture;
}

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec3 v_position;
in vec4 v_color;
in vec2 v_texcoord;
in vec3 v_normal;

//uniform vec4 u_color;
uniform sampler2D u_texture0;


struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main(){
//    color = v_color;


    vec4 tex1 = texture2D(u_texture0, v_texcoord);
    if(tex1.a == 0){
        discard;
    }
    color = tex1;
}

#shader geometry
#version 440 core

int main(){
return 0;
}
