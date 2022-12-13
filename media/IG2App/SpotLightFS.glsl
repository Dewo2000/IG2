#version 330 core
uniform sampler2D textureM;  
uniform vec4 lightPosition;
uniform mat4 normalMat;
uniform float BF; 
uniform float intLuzAmb; 
uniform float cutoff;
in vec2 vUv0; 
in vec3 mNormal;
in vec3 viewVertex;
out vec4 fFragColor; 

float diff(vec3 cVertex, vec3 cNormal){
    vec3 lightDir = lightPosition.xyz;
    if(lightPosition.w == 1)
        lightDir = lightPosition.xyz - cVertex;
    return dot(cNormal, normalize(lightDir));
}

void main() {
    vec3 viewNormal = normalize(vec3(normalMat * vec4(mNormal,0)));
    float diffuse = diff(lightPosition.xyz, viewNormal);
    vec3 colorM =  texture(textureM,vUv0).rgb;
    vec3 color = colorM;
    if(diffuse < cutoff+1){
        color = colorM * 0.2;
    }
    fFragColor = vec4(color, 1.0); 
}