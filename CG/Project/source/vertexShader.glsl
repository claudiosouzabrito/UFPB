#version 400 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoords;
layout (location = 2) in vec3 normalVector;
out vec3 fragPos;
out vec2 pass_textureCoords;
out vec3 aNormal;
uniform mat4 transform;

//Declaraçoes da perspectiva
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;

void main()
{
	//gl_Position = vec4(position, 1.0);
	gl_Position = projection * view *  transform * vec4(position, 1.0);
	aNormal = inverse(transpose(mat3(transform)))  *  normalVector;
	pass_textureCoords = textureCoords;
	fragPos = vec3(transform * vec4(position, 1.0));
}