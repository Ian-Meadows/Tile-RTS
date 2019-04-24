#version 450 core
out vec4 FragColor;

in vec3 oPos;

void main(){
	FragColor = vec4(oPos.x, oPos.y, oPos.x/oPos.y , 1.0f);
}