#version 330 core
//Hopefully this will be a temporary shader and I will get around to deferred shading
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec3 worldPosition;
out vec2 texCoords;
out vec3 worldNormal;

uniform mat4 model;
uniform mat3 transInvModel; //Used to correct normals
uniform mat4 view;
uniform mat4 projection;

void main(){
	//Convert position to model space
	worldPosition = vec3(model * vec4(vertexPosition, 1.0));
	//Convert normal to model space
	worldNormal = transInvModel * vertexNormal;
	//Pass texture coords to fragment shader
	texCoords = vertexUV;
	gl_Position = projection * view * vec4(worldPosition, 1.0);
}
