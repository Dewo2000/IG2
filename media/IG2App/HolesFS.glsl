#version 330 core
uniform sampler2D texFront; 
uniform sampler2D texBack; 
uniform sampler2D checkTex; 
uniform float BF; 
uniform float intLuzAmb; 
in vec2 vUv0; 
out vec4 fFragColor; 
void main() {
    vec3 colorCheck = texture(texturaL, vUv0).rgb;
    if (colorCheck.x > 0.6) discard;
    vec3 frontcolor = vec3(texture(texFront, vUv0)); 
    vec3 backcolor = vec3(texture(texBack, vUv0));
    vec3 color = backcolor;
    if (gl_FrontFacing) {
        color = frontcolor;
    }
    fFragColor = vec4(color, 1.0); 
}