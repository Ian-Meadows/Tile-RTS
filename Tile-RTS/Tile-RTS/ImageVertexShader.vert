#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int totalImages;
uniform int imgSize;
uniform int unit;
uniform int spacing;


out vec3 oPos;
out vec2 TexCoord;

void main()
{
    gl_Position = projection *  view * model * vec4(aPos, 1.0);
	//gl_Position = vec4(aPos, 1.0);
	//gl_Position = projection *  view * vec4(aPos, 1.0);
	oPos = aPos;

	float s = (imgSize / float(totalImages)) * unit;
	int size = int(ceil(sqrt(totalImages)));

	int y = int(mod(unit, size));
	int x = (unit - y) / size;

	float xSpacing = spacing / float(imgSize);
	float ySpacing = spacing / float(imgSize);

	float sx = (1.0f / float(size)) * float(x);
	float sy = (1.0f / float(size)) * float(y);
	
	TexCoord = texCoords;
	TexCoord.x = (TexCoord.x / float(size)) + sx;
	TexCoord.y = (TexCoord.y / float(size)) + sy;
}