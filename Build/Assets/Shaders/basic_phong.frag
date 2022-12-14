#version 430 core

in vec3 position;
in vec3 normal;
in vec2 texcoord;

out vec4 fcolor;

struct Light
{
		vec3 ambient;
		vec3 color;
		vec4 position;
};

struct Material
{
	vec3 color;
	float shininess;
};

uniform Light light;
uniform Material material;

uniform sampler2D textureSampler;

void main()
{
	vec3 ambient = light.ambient * material.color;

	vec3 light_dir = normalize(vec3(light.position) - position);

	float intensity = max(dot(light_dir, normal), 0);
	vec3 diffuse = light.color * material.color * intensity;

	vec3 specular = vec3(0);
	if (intensity > 0)
	{
		vec3 reflection = reflect(-light_dir, normal);
		vec3 view_dir = normalize(-vec3(position));
		intensity = max(dot(reflection, view_dir), 0);
		intensity = pow(intensity, material.shininess);
		specular = light.color *material.color * intensity;
	}


	//fcolor = vec4(color * tint, 1.0);

	fcolor = vec4(ambient + diffuse, 1) * texture(textureSampler, texcoord) + vec4 (specular, 1);
}
