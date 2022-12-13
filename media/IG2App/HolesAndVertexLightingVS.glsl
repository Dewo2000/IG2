#version 330 core
in vec4 vertex; 
in vec2 uv0; 
in vec3 normal;

uniform mat4 modelViewProjMat; 
uniform mat4 modelViewMat;
uniform mat4 normalMat;
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform vec3 materialDiffuse;

out vec2 vUv0;
out vec3 vFrontColor;
out vec3 vBackColor;

float diff(vec3 cVertex, vec3 cNormal){
    vec3 lightDir = lightPosition.xyz;
    if(lightPosition.w == 1)
        lightDir = lightPosition.xyz - cVertex;
    return max(dot(cNormal, normalize(lightDir)), 0.0);
}

void main() {
    vec3 viewVertex = vec3(modelViewMat * vertex);
    vec3 viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
    vec3 diffuse = diff(viewVertex, viewNormal) *
    lightDiffuse * materialDiffuse;
    vFrontColor = diffuse * vec3(0.72,0.57,0.35);
    diffuse = diff(viewVertex, -viewNormal) *
    lightDiffuse * materialDiffuse;
    vBackColor = diffuse * vec3(0.0,0.6,0.83); 
    vUv0 = uv0; 
    gl_Position = modelViewProjMat * vertex; 
}
