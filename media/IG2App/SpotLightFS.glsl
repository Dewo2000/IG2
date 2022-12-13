#version 330 core
uniform sampler2D textureM;  


uniform float BF; 
uniform float intLuzAmb; 
uniform float cutoff;
in vec2 vUv0; 
in vec3 mNormal;
out vec4 fFragColor; 

void main() {
    vec3 viewNormal = normalize(vec3(mNormal));
    float diffuse = dot(viewNormal,normalize(vec3(0,1,0)));
    vec3 colorM =  texture(textureM,vUv0).rgb;
    vec3 color = colorM;
    if(diffuse < cutoff+1){
        color = colorM * 0.2;
    }
    fFragColor = vec4(color, 1.0); 
}