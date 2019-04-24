#version 450

out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	//sampler2D specular;
	float shininess;
};

struct Light {
	//vec3 position;
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

//uniform vec3 lightPos;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

// texture samplers
uniform sampler2D texture1;

void main()
{
	// ambient
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoord).rgb;

	// diffuse 
	vec3 norm = normalize(Normal);
	//vec3 lightDir = normalize(light.position - FragPos);	//Test Light
	vec3 lightDir = normalize(-light.direction);			//Directional Light
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoord).rgb;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);
	
	//FragColor = texture(texture1, TexCoord);
}