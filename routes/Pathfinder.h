#pragma once

#include <deque>
#include <queue>
#include "vec2i.h"

class Pathfinder {
private:
	vec2i& start;
	std::deque<vec2i>& targets;
	bool finished = false;

	int mapWidth, mapHeight;

	enum neighbor {
		right = 0b0001,
		up = 0b0010,
		left = 0b0100,
		down = 0b1000
	};
	neighbor neighborTypes[4]{ down,right,left,up };
	neighbor reverseDirection(neighbor dir);

	vec2i getDirection(neighbor dir);
	inline bool isInMap(const vec2i& pos);
	inline double getDistance(const vec2i& a, const vec2i& b);
	vec2i getFarthestTargetPosition();

public:
	Pathfinder(vec2i& start, std::deque<vec2i>& targets, int mapWidth, int mapHeight);
	void discoverMap_BFS(int* map, int* discovered);
	void discoverMap_A_STAR(int* map, int* discovered);
	int getSumPathLength(std::deque<vec2i>& targets, int* discovered);
};
