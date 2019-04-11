#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in ivec2 bPos;
layout (location = 2) in ivec2 unitInformation;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 oPos;
flat out ivec2 unitInfo;

void main()
{
    gl_Position = projection *  view * model * vec4(aPos.x + bPos.x, aPos.y + bPos.y, aPos.z, 1.0);
	//gl_Position = vec4(aPos, 1.0);
	//gl_Position = projection *  view * vec4(aPos, 1.0);
	oPos = aPos * unitInformation.x;
	unitInfo = unitInformation;
	oPos.x = unitInformation.x;
	
}