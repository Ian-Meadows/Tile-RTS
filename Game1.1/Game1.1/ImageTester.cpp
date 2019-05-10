#include "ImageTester.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Window.h"
#include "TextureAtlasCreator.h"
#include "Time.h"


ImageTester::ImageTester()
{
	position = glm::vec3(-200, -200, 0);
	rotation = 0.0f;
	size = 200;

	shader = new Shader("ImageVertexShader.vert", "ImageFragmentShader.frag");

	InitShape();
	InitTexture();
}


ImageTester::~ImageTester()
{
	delete shader;
}

void ImageTester::InitShape() {
	glGenVertexArrays(1, &VAO);

	//0:verticies
	//1:texture coords
	glGenBuffers(2, VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);

	float vert[] = {
			0.5f,  0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indi[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indi), indi, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	float diff = TextureAtlasCreator::GetSpacing() * TextureAtlasCreator::GetImagesPerLength() / (float)TextureAtlasCreator::GetWidth();

	//std::cout << diff <<

	float texCoords[] = {
		1.0f - diff, 1.0f - diff,
		1.0f - diff, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f - diff
	};

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

}

void ImageTester::InitTexture() {
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int width = TextureAtlasCreator::GetWidth();
	int height = TextureAtlasCreator::GetHeight();

	int size;
	char* image = TextureAtlasCreator::CompressTextureAtlas(&size);

	if (image == nullptr) {
		std::cout << "unable to load image to texture" << std::endl;
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	//free image
	delete[] image;

	shader->use();
	shader->setInt("ourTexture", 0);

}

void ImageTester::Update() {
	t += Time::GetDeltaTime();
	if (t > 1.0) {
		t = 0;
		unitNum++;
		if (unitNum >= TextureAtlasCreator::GetTotalImages()) {
			unitNum = 0;
			std::cout << "flip" << std::endl;
		}
	}
}

glm::mat4 ImageTester::GetModel() {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(size, size, size));
	return model;
}



void ImageTester::Draw() {
	shader->use();
	shader->setMat4("projection", Window::GetPerspective());
	shader->setMat4("view", Camera::GetView());
	shader->setMat4("model", GetModel());

	shader->setInt("totalImages", TextureAtlasCreator::GetTotalImages());
	shader->setInt("imgSize", TextureAtlasCreator::GetWidth());
	shader->setInt("unit", unitNum);
	shader->setInt("spacing", TextureAtlasCreator::GetSpacing());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
