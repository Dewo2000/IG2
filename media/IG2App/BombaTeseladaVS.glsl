#version 330 core
in vec4 vertex; 
in vec2 uv0; 
uniform mat4 modelViewProjMat; 
out vec2 vUv0;
void main() {
    vUv0 = vec2(0,0) ;     
}