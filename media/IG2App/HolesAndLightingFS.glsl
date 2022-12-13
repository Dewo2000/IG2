#version 330 core
uniform sampler2D checkTex; 
uniform sampler2D texBack; 
uniform sampler2D texFront; 

uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform vec3 materialDiffuse;

uniform mat4 normalMat;

uniform float BF; 
uniform float intLuzAmb; 
in vec2 vUv0; 
in vec3 Normal;
in vec3 viewVertex;
out vec4 fFragColor; 

float diff(vec3 cVertex, vec3 cNormal){
    vec3 lightDir = lightPosition.xyz;
    if(lightPosition.w == 1)
        lightDir = lightPosition.xyz - cVertex;
    return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
   
    vec3 viewNormal = normalize(vec3(normalMat * vec4(Normal,0)));
    vec3 diffuse = diff(viewVertex, viewNormal) *
    lightDiffuse * materialDiffuse;
    vec3 vFrontColor = diffuse * vec3(0.72,0.57,0.35) * texture(texFront,vUv0).rgb;
    diffuse = diff(viewVertex, -viewNormal) *
    lightDiffuse * materialDiffuse;
    vec3 vBackColor = diffuse * vec3(0.0,0.6,0.83)* texture(texBack,vUv0).rgb; 

    vec3 colorCheck = texture(checkTex, vUv0).rgb;
    if (colorCheck.x > 0.6) discard;
    vec3 color = vBackColor;
    if (gl_FrontFacing) {
        color =  vFrontColor;
    }
    fFragColor = vec4(color, 1.0); 
}