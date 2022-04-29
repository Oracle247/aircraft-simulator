#shader vertex
#version 440 core

layout(location = 0) in vec3 position;

out vec3 TexCoords;

uniform mat4 view;
uniform mat4 projection;

void main(){
    TexCoords = position;
    gl_Position = projection * view * vec4(position, 1.0f);
    //gl_Position = pos.xyww;
    //v_position = vec4(model * vec4(position, 1.0f)).xyz;

}

#shader fragment
#version 440 core

layout(location = 0) out vec4 color;

in vec3 TexCoords;

uniform samplerCube u_texture0;

//uniform vec3 ambient;
//uniform vec3 diffuse;


void main(){

    //ambient light
//    vec3 ambientLight = ambient;

    //vec4 texColor = tex1 * tex2;
    color = textureCube(u_texture0, TexCoords);
}



