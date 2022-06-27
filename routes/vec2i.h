#pragma once

struct vec2i {
	int x, y;

	bool operator==(const vec2i& other) const {
		return this->x == other.x && this->y == other.y;
	}
	bool operator!=(const vec2i& other) const {
		return !(*this == other);
	}
	vec2i operator+(const vec2i& other) const {
		return { this->x + other.x,this->y + other.y };
	}
};