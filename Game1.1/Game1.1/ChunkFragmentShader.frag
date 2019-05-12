#version 450 core
out vec4 FragColor;

in vec3 oPos;
//must be in hexidecimal ex. white:0xffffff. Note: alpha is not included
flat in int unitColor;
in vec2 texCoord;

uniform sampler2D chunkTexture;
uniform int chunkSize;



//shift 16 bits for red location
#define MASK_R 255 << 16
//shift 8 bits for green location
#define MASK_G 255 << 8
//don't need to shift because bits are already set for blue
#define MASK_B 255

vec4 GetColor(){

	int r, g, b;

	//outside of hex range(might wanna remove)
	if(unitColor > 16777215 || unitColor < 0){
	//return a wild pink color
		return vec4(0.95f, 0.11f, 0.87f, 1.0f);
	}
	
	//Use mask to retrive the red hex number. Then shift back 16 to get a number between 0 and 255.
	r = (unitColor & MASK_R) >> 16;
	//Use mask to retrieve the green hex number. Then shift back 8 to get a number between 0 and 255.
	g = (unitColor & MASK_G) >> 8;
	//Use mask to retrieve the blue hex number.
	b = unitColor & MASK_B;

	//r, g, b need to be converted from integers betweet 0 and 255 to floats between 0.0f and 1.0f
	return vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);

}


void main(){
	
	/*
	float posX = gl_FragCoord.x / chunkSize;

	//FragColor = vec4(oPos.x, oPos.y, oPos.x/oPos.y , 1.0f);

	if(mod(unitInfo.x,5) <= 2){
		FragColor = vec4(texCoord.x, oPos.y, unitInfo.y , 1.0f);
	}
	else{
		FragColor = vec4(1, oPos.y, 0 , 1.0f);
	}
	*/

	FragColor = texture(chunkTexture, texCoord) * GetColor();
	
	
	
}