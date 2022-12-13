#version 330 core
out vec4 fFragColor;
uniform sampler2D texturaL; 
uniform sampler2D texturaM; 
uniform sampler2D texturaX; 
uniform float BF; 
uniform float intLuzAmb; 
in vec2 vUv0; 

void main(){
    vec3 colorL = vec3(texture(texturaL, vUv0)); 
    vec3 colorM = vec3(texture(texturaM, vUv0));
    vec3 color = mix(colorL,colorM,colorX, BF) * intLuzAmb;
    fFragColor = vec4(color,1.0);
}