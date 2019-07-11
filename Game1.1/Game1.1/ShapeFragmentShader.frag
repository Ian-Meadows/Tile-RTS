#version 450 core

out vec4 FragColor;

uniform int color;

//shift 16 bits for red location
#define MASK_R 255 << 16
//shift 8 bits for green location
#define MASK_G 255 << 8
//don't need to shift because bits are already set for blue
#define MASK_B 255

vec4 GetColor(){

	int r, g, b;

	//outside of hex range(might wanna remove)
	if(color > 16777215 || color < 0){
	//return a wild pink color
		return vec4(0.95f, 0.11f, 0.87f, 1.0f);
	}
	
	//Use mask to retrive the red hex number. Then shift back 16 to get a number between 0 and 255.
	r = (color & MASK_R) >> 16;
	//Use mask to retrieve the green hex number. Then shift back 8 to get a number between 0 and 255.
	g = (color & MASK_G) >> 8;
	//Use mask to retrieve the blue hex number.
	b = color & MASK_B;

	//r, g, b need to be converted from integers betweet 0 and 255 to floats between 0.0f and 1.0f
	return vec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);

}


void main(){
	
	FragColor = GetColor();
	
}