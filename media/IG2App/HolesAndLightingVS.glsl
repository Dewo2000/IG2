#version 330 core
in vec4 vertex; 
in vec2 uv0; 
in vec3 normal;

uniform mat4 modelViewProjMat; 
uniform mat4 modelViewMat;

out vec2 vUv0;
out vec3 Normal;
out vec3 viewVertex;
void main() {
    viewVertex = vec3( * vertex);
    Normal = normal;
    vUv0 = uv0; 
    gl_Position = modelViewProjMat * vertex; 
}