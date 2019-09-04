#version 450 core
out vec4 FragColor;

in vec3 oPos;
//must be in hexidecimal ex. white:0xffffff. Note: alpha is not included
flat in int unitColor;
in vec2 texCoord;
in vec2 unitSelectionTexCoord;

//tile textures info
flat in int tileColor;
in vec2 tileTexCoords;


//supposed to be bools
#define TRUE 1
#define FALSE 0
flat in int isSolidColor;//1:true //0:false
flat in int isSelected;//1:true //0:false
flat in int tileIsSolidColor;//1:true //0:false

uniform sampler2D chunkTexture;
uniform sampler2D unitSelectionTexture;

uniform int chunkSize;
uniform vec3 unitSelectionColor;


//shift 16 bits for red location
#define MASK_R 255 << 16
//shift 8 bits for green location
#define MASK_G 255 << 8
//don't need to shift because bits are already set for blue
#define MASK_B 255
/*
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
*/

vec4 GetColor(int color){

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

//returns first vector if w scalar is greater then 0 otherwise the second vector is returned.
vec4 GetVectorWithPriority(vec4 priority, vec4 extra){
	if(priority.w > 0.0f){
		return priority;
	}
	else{
		return extra;
	}
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

	//dont render background tile
	if(isSolidColor == TRUE){
		if(isSelected == TRUE){
			FragColor = GetVectorWithPriority(texture(unitSelectionTexture, unitSelectionTexCoord) * vec4(unitSelectionColor, 1.0f),
				GetColor(unitColor));
		}
		else{
			FragColor = GetColor(unitColor);
		}
		
	}
	else{
		
		if(isSelected == TRUE){
			FragColor = GetVectorWithPriority(texture(unitSelectionTexture, unitSelectionTexCoord) * vec4(unitSelectionColor, 1.0f),
				texture(chunkTexture, texCoord) * GetColor(unitColor));
		}
		else{
			//texture(chunkTexture, tileTexCoords) * GetColor(tileColor);
			//FragColor = texture(chunkTexture, texCoord) * GetColor(unitColor);
			if(tileIsSolidColor == TRUE){
			/*
				FragColor = GetVectorWithPriority(texture(chunkTexture, texCoord) * GetColor(unitColor),
					GetColor(tileColor));
					*/
					if(tileTexCoords.x == -1){
						FragColor = GetColor(0xff00ff);
					}
					else{
						FragColor = GetColor(0xff00ff);
					}
					
			}
			else{
			/*
				FragColor = GetVectorWithPriority(texture(chunkTexture, texCoord) * GetColor(unitColor),
					texture(chunkTexture, tileTexCoords) * GetColor(tileColor));
					*/
					//FragColor = texture(chunkTexture, tileTexCoords) * GetColor(0xff00ff);
					FragColor = GetColor(0xff00ff);
			}
			
			
		}
	}
	
	
}