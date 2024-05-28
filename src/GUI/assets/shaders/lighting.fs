#version 330

// Input vertex attributes (from vertex shader)
in vec3 fragPosition;
in vec3 fragNormal;
in vec2 fragTexCoord;

// Input uniform values
uniform sampler2D texture0;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
uniform vec3 lightColor;
uniform vec3 ambientColor;
uniform vec3 objectColor;  // Ajout d'une couleur uniforme pour l'objet

// Output fragment color
out vec4 fragColor;

void main()
{
    // Ambient lighting
    vec3 ambient = ambientColor;
    
    // Diffuse lighting
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // Specular lighting
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * lightColor;

    // Utiliser la couleur uniforme pour l'objet
    vec3 resultColor = objectColor;

    vec3 result = (ambient + diffuse + specular) * resultColor;
    fragColor = vec4(result, 1.0);
}
