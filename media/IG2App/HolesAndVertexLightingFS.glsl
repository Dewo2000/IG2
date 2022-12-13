#version 330 core
uniform sampler2D texFront; 
uniform sampler2D texBack; 
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
    vec3 frontcolor = texture(texFront, vUv0).rgb; 
    vec3 backcolor = texture(texBack, vUv0).rgb;
    vec3 color = backcolor * vBackColor;
    if (gl_FrontFacing) {
        color = frontcolor * vFrontColor;
    }
    fFragColor = vec4(color, 1.0); 
}