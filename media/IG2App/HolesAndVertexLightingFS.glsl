#version 330 core
uniform sampler2D checkTex; 
uniform float BF; 
uniform float intLuzAmb; 
in vec2 vUv0; 
in vec3 vFrontColor;
in vec3 vBackColor;
out vec4 fFragColor; 
void main() {
    vec3 colorCheck = texture(checkTex, vUv0).rgb;
    if (colorCheck.x > 0.6) discard;
    vec3 color = vBackColor;
    if (gl_FrontFacing) {
        color =  vFrontColor;
    }
    fFragColor = vec4(color, 1.0); 
}