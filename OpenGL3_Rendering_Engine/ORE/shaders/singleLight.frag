#version 330 core
//Hopefully this will be a temporary shader and I will get around to deferred shading
out vec4 color;

in vec3 worldPosition;
in vec2 texCoords;
in vec3 worldNormal;

struct DirectionalLight {
	vec3 direction;
};

struct PointLight {
	vec3 position;
	//Attenuation
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	//
	float cutOff;
	float outerCutOff;
	//Attenuation
	float constant;
	float linear;
	float quadratic;
};

//Shared properties
struct AllLights {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//Material properties
uniform sampler2D diffuse;
uniform sampler2D specular;
uniform float shininess;

//Light properties
uniform int lightType; //0=DirectionalLight, 1=PointLight, 2=SpotLight
uniform DirectionalLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;
uniform AllLights light;

uniform vec3 viewPos;

void calcDirectional();
void calcPointLight();
void calcSpotLight();

void main(){
	if(lightType == 0){
		calcDirectional();
	} else if(lightType == 1) {
		calcPointLight();
	} else if(lightType == 2) {
		calcSpotLight();
	}
}

void calcDirectional(){
	//Calculate directions
	vec3 lightDir = normalize(-dirLight.direction);
	vec3 norm = normalize(worldNormal);
	vec3 viewDir = normalize(viewPos - worldPosition);
	vec3 halfDir = normalize(lightDir + viewDir);
	//Textures used to get material properties
	vec3 diffuseTex = texture(diffuse, texCoords).rgb;
	vec3 specularTex = texture(specular, texCoords).rgb;
	//Get ambient colours
	vec3 a = light.ambient * diffuseTex;
	//Get diffuse colours
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 d = light.diffuse * diff * diffuseTex;
	//Get specular colours
	float spec = pow(max(dot(norm, halfDir), 0.0), shininess);
	vec3 s = light.specular * spec * specularTex;
	//Combine 3 colours
	color = vec4(a + d + s, 1.0);
}

void calcPointLight(){
	//Calculate directions
	vec3 lightDir = normalize(pointLight.position - worldPosition);
	vec3 norm = normalize(worldNormal);
	vec3 viewDir = normalize(viewPos - worldPosition);
	vec3 halfDir = normalize(lightDir + viewDir);
	//Textures used to get material properties
	vec3 diffuseTex = texture(diffuse, texCoords).rgb;
	vec3 specularTex = texture(specular, texCoords).rgb;
	//Get ambient colours
	vec3 a = light.ambient * diffuseTex;
	//Get diffuse colours
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 d = light.diffuse * diff * diffuseTex;
	//Get specular colours
	float spec = pow(max(dot(norm, halfDir), 0.0), shininess);
	vec3 s = light.specular * spec * specularTex;
	//Combine 3 colours
	float dist = length(pointLight.position - worldPosition);
	float att = 1.0 / (pointLight.constant + pointLight.linear * dist +
	            pointLight.quadratic * (dist * dist));
	color = vec4((a + d + s) * att, 1.0);
}

void calcSpotLight(){
	vec3 lightDir = normalize(spotLight.position - worldPosition);
	//Calculate cone
	float theta = dot(lightDir, normalize(-spotLight.direction));
	float epsilon = spotLight.cutOff - spotLight.outerCutOff;
	float intensity = clamp((theta - spotLight.outerCutOff) / epsilon, 0.0, 1.0);
	vec3 diffuseTex = texture(diffuse, texCoords).rgb;
	//Calculate attenuation
	float dist = length(spotLight.position - worldPosition);
	float att = 1.0 / (spotLight.constant + spotLight.linear * dist +
	            spotLight.quadratic * (dist * dist));
	if(theta > spotLight.outerCutOff){
		//Calculate directions
		vec3 norm = normalize(worldNormal);
		vec3 viewDir = normalize(viewPos - worldPosition);
		vec3 halfDir = normalize(lightDir + viewDir);
		//Textures used to get material properties
		vec3 specularTex = texture(specular, texCoords).rgb;
		//Get ambient colours
		vec3 a = light.ambient * diffuseTex;
		//Get diffuse colours
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 d = light.diffuse * diff * diffuseTex;
		//Get specular colours
		float spec = pow(max(dot(norm, halfDir), 0.0), shininess);
		vec3 s = light.specular * spec * specularTex;
		//Combine 3 colours
		color = vec4((a + d * intensity + s * intensity) * att, 1.0);
	}else{
		//color = vec4(0.0, 0.0, 0.0, 0.0);
		color = vec4(light.ambient * diffuseTex * att, 1.0);
	}
}
