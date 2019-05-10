#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in ivec2 bPos;
layout (location = 2) in ivec2 unitInformation;
layout (location = 3) in vec2 wholeTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int totalImages;
uniform int imgSize;
uniform int spacing;

out vec3 oPos;
flat out int unitColor;
out vec2 texCoord;


void SetTextCoords(){

	//texCoords = wholeTexCoords;
	//return;
	
	int unit = unitInformation.x;

	//float s = (imgSize / float(totalImages)) * unit;
	int size = int(ceil(sqrt(totalImages)));

	int y = int(mod(unit, size));
	int x = (unit - y) / size;

	float xSpacing = spacing / float(imgSize);
	float ySpacing = spacing / float(imgSize);

	float sx = (1.0f / float(size)) * float(x);
	float sy = (1.0f / float(size)) * float(y);
	
	texCoord = wholeTexCoords;
	texCoord.x = (texCoord.x / float(size)) + sx;
	texCoord.y = (texCoord.y / float(size)) + sy;
	
}

void main()
{
    gl_Position = projection *  view * model * vec4(aPos.x + bPos.x, aPos.y + bPos.y, aPos.z, 1.0);
	//gl_Position = vec4(aPos, 1.0);
	//gl_Position = projection *  view * vec4(aPos, 1.0);
	oPos = aPos * unitInformation.x;
	oPos.x = unitInformation.x;
	SetTextCoords();
	unitColor = unitInformation.y;
}