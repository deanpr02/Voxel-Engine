#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
    {   
        //diffuse lighting
        vec3 norm = normalize(Normal);
        vec3 lightDir = normalize(lightPos - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * lightColor;
        
        //ambient lighting
        vec3 objectColor = vec3(0.8f,0.8f,0.8f);
        vec3 ambient = ambientStrength * lightColor;

        //specular lighting
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir),0.0),64);
        vec3 specular = specularStrength * spec * lightColor;

        // Attenuation
        float distance = length(lightPos - FragPos);
        float attenuation = clamp(1.0/distance,0.0,1.0);

        vec3 result = ((ambient + specular + diffuse) * attenuation) * objectColor;
        //vec3 result = (ambient + diffuse + specular) * objectColor;

        FragColor = vec4(result,1.0);
    };