#pragma once
#include <glm/glm.hpp>

#include "UIHandler.h"

namespace ScreenMath {

	//without size


	glm::vec2 GetLeft() {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(-(resolution.x / UI_PERSPECTIVE_SCALE), 0.0f);
	}
	glm::vec2 GetRight() {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(resolution.x / UI_PERSPECTIVE_SCALE, 0.0f);
	}
	glm::vec2 GetTop() {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(0.0f, resolution.y / UI_PERSPECTIVE_SCALE);
	}
	glm::vec2 GetBottom() {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(0.0f, -(resolution.y / UI_PERSPECTIVE_SCALE));
	}

	glm::vec2 GetUpperLeft() {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(-(resolution.x / UI_PERSPECTIVE_SCALE), resolution.y / UI_PERSPECTIVE_SCALE);
	}
	glm::vec2 GetUpperRight() {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(resolution.x / UI_PERSPECTIVE_SCALE, resolution.y / UI_PERSPECTIVE_SCALE);
	}
	glm::vec2 GetLowerLeft() {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(-(resolution.x / UI_PERSPECTIVE_SCALE), -(resolution.y / UI_PERSPECTIVE_SCALE));
	}
	glm::vec2 GetLowerRight() {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(resolution.x / UI_PERSPECTIVE_SCALE, -(resolution.y / UI_PERSPECTIVE_SCALE));
	}





	//with size


	glm::vec2 GetLeft(glm::vec2 size) {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2((-resolution.x / UI_PERSPECTIVE_SCALE) + (size.x / 2), 0.0f);
	}
	glm::vec2 GetRight(glm::vec2 size) {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2((resolution.x / UI_PERSPECTIVE_SCALE) - (size.x / 2), 0.0f);
	}
	glm::vec2 GetTop(glm::vec2 size) {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(0.0f, (resolution.y / UI_PERSPECTIVE_SCALE) - (size.y / 2));
	}
	glm::vec2 GetBottom(glm::vec2 size) {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2(0.0f, (-resolution.y / UI_PERSPECTIVE_SCALE) + (size.y / 2));
	}

	glm::vec2 GetUpperLeft(glm::vec2 size) {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2((-resolution.x / UI_PERSPECTIVE_SCALE) + (size.x / 2), (resolution.y / UI_PERSPECTIVE_SCALE) - (size.y / 2));
	}
	glm::vec2 GetUpperRight(glm::vec2 size) {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2((resolution.x / UI_PERSPECTIVE_SCALE) - (size.x / 2), (resolution.y / UI_PERSPECTIVE_SCALE) - (size.y / 2));
	}
	glm::vec2 GetLowerLeft(glm::vec2 size) {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2((-resolution.x / UI_PERSPECTIVE_SCALE) + (size.x / 2), (-resolution.y / UI_PERSPECTIVE_SCALE) + (size.y / 2));
	}
	glm::vec2 GetLowerRight(glm::vec2 size) {
		glm::ivec2 resolution = UIHandler::GetResolution();
		return glm::vec2((resolution.x / UI_PERSPECTIVE_SCALE) - (size.x / 2), (-resolution.y / UI_PERSPECTIVE_SCALE) + (size.y / 2));
	}
}