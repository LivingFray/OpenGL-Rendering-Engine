#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
//layout(location = 2) in vec3 vertexNormal;

out vec2 texCoords;

uniform mat4 mvp;

void main(){
	gl_Position = mvp * vec4(vertexPosition, 1);
	texCoords = vertexUV;
}