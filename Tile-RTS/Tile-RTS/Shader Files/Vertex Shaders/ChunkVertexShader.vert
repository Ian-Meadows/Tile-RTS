#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in ivec2 bPos;
layout (location = 2) in ivec2 unitInformation;
layout (location = 3) in vec2 wholeTexCoords;
layout (location = 4) in vec2 basicTexCoords;

//x:image number from texture atlas
//y:color
uniform ivec2 backgroundTiles[255];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform int totalImages;
uniform int imgSize;
uniform int spacing;


//basic textures info
flat out int unitColor;
out vec2 texCoord;
out vec2 unitSelectionTexCoord;

//tile textures info
flat out int tileColor;
out vec2 tileTexCoords;

#define TRUE 1
#define FALSE 0
//supposed to be bools
flat out int isSolidColor;//1:true //0:false
flat out int isSelected;//1:true //0:false
flat out int tileIsSolidColor;//1:true //0:false



//unit type constants(sent from cpu)
uniform int SOLIDCOLOR;


#define MASK_TILE 255 << 24



/*
void SetTextCoords(){

	//texCoords = wholeTexCoords;
	//return;
	
	int unit = unitInformation.x;
	if(unit < 0){
		unit *= -1;
		isSelected = 1;
	}
	if(unit == SOLIDCOLOR){
		texCoord.x = -1;
		texCoord.y = -1;
		isSolidColor = 1;
		return;
	}
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

	isSolidColor = 0;
}
*/

vec2 GetAtlasCoords(int unit){

	int size = int(ceil(sqrt(totalImages)));

	int y = int(mod(unit, size));
	int x = (unit - y) / size;

	float xSpacing = spacing / float(imgSize);
	float ySpacing = spacing / float(imgSize);

	float sx = (1.0f / float(size)) * float(x);
	float sy = (1.0f / float(size)) * float(y);
	
	vec2 tempCoord = wholeTexCoords;
	tempCoord.x = (tempCoord.x / float(size)) + sx;
	tempCoord.y = (tempCoord.y / float(size)) + sy;

	return tempCoord;
}

//want to use unitInformation.y of position alpha
void GetBackgroundTile(){
	int color = unitInformation.y;

	//mask
	int tile = (color & MASK_TILE) >> 24;

	//reverse mask
	unitColor = (color - (tile << 24));
	

	//check if tile exists
	if(backgroundTiles[tile].x == -1){
		tileColor = 0xf000f0;
		tileTexCoords = vec2(-1, -1);
		tileIsSolidColor = TRUE;
		return;
	}

	tileColor = backgroundTiles[tile].y;
	
	

	int tileType = backgroundTiles[tile].x;
	if(tileType == SOLIDCOLOR){
		tileTexCoords = vec2(-1, -1);
		tileIsSolidColor = TRUE;
	}
	else{
		tileTexCoords = GetAtlasCoords(tileType);
		tileIsSolidColor = FALSE;
	}

}

void HandleMainTexture(){

	int unit = unitInformation.x;

	if(unit < 0){
		unit *= -1;
		isSelected = TRUE;
	}
	else{
		isSelected = FALSE;
	}
	if(unit == SOLIDCOLOR){
		texCoord.x = -1;
		texCoord.y = -1;
		isSolidColor = TRUE;
	}
	else{
		isSolidColor = FALSE;
		texCoord = GetAtlasCoords(unit);
	}
}



void main()
{
    gl_Position = projection *  view * model * vec4(aPos.x + bPos.x, aPos.y + bPos.y, aPos.z, 1.0);
	//gl_Position = vec4(aPos, 1.0);
	//gl_Position = projection *  view * vec4(aPos, 1.0);
	//SetTextCoords();

	GetBackgroundTile();
	HandleMainTexture();
	
	//unitColor = unitInformation.y;

	unitSelectionTexCoord = basicTexCoords;
}