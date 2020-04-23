#version 400 core

in vec2 pass_textureCoords;
in vec3 aNormal;  
in vec3 fragPos;
out vec4 out_Color;
uniform vec3 lightPos; 
uniform sampler2D textureSampler;
uniform vec3 lightamb;
uniform vec3 lightfont;
uniform float lightIntensity;
uniform vec3 objectColor;
uniform vec3 viewPos;

//vec3 colorA = vec3(0.149,0.141,0.912);
float specularStrength = 0.5;

void main()
{
  
    //ambiente
    vec3 AmbientColor = lightamb * lightIntensity;
    //difuso
    vec3 norm = normalize(aNormal);
    vec3 lightDir = normalize(lightPos - fragPos) ;
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightfont * 1;
    //especular
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightfont * 1; 
    //total
    vec4 cores = vec4(((AmbientColor + diffuse + specular) * objectColor), 1.0f);
    out_Color = texture(textureSampler, pass_textureCoords) * cores ;
}
