#shader vertex
#version 440 core


layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texture;
layout(location = 3) in vec3 normal;

out vec4 v_color;
out vec2 v_texcoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){
    gl_Position = projection * view * model * vec4(position, 1.0f);
    v_color = vec4(color, 1.0f);
    v_texcoord = texture;
    //gl_Position = pos.xyww;
    //v_position = vec4(model * vec4(position, 1.0f)).xyz;

}

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec2 v_texcoord;
in vec4 v_color;

uniform sampler2D u_texture0;

//uniform vec3 ambient;
//uniform vec3 diffuse;


void main(){

    //ambient light
//    vec3 ambientLight = ambient;

    //vec4 texColor = tex1 * tex2;
    vec4 tex = texture2D(u_texture0, v_texcoord);
    color = tex * v_color;
}



