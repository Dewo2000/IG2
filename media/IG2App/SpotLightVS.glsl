#version 330 core
in vec4 vertex; 
in vec3 normal;
in vec2 uv0; 
uniform mat4 modelViewProjMat; 
uniform mat4 modelViewMat;
out vec2 vUv0;
out vec3 mNormal;
void main() {
    mNormal = normal;
    vUv0 = uv0; 
    gl_Position = modelViewProjMat * vertex; 
}