#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 oPos;
out vec2 TexCoord;

void main()
{
    gl_Position = projection *  view * model * vec4(aPos, 1.0);
	//gl_Position = vec4(aPos, 1.0);
	//gl_Position = projection *  view * vec4(aPos, 1.0);
	oPos = aPos;
	TexCoord = texCoords;
}