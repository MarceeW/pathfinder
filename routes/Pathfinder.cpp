#include "Pathfinder.h"

Pathfinder::neighbor Pathfinder::reverseDirection(neighbor dir) {
	if (dir & 0b1100)
		return neighbor(dir >> 0b0010);
	else return neighbor(dir << 0b0010);
}

vec2i Pathfinder::getDirection(neighbor dir) {
	if (dir & down) return { 0,1 };
	else if (dir & right) return { 1,0 };
	else if (dir & left) return { -1,0 };
	return { 0,-1 };
}
inline bool Pathfinder::isInMap(const vec2i& pos) {
	return pos.x >= 0 && pos.x < mapWidth&& pos.y >= 0 && pos.y < mapHeight;
}
inline double Pathfinder::getDistance(const vec2i& a, const vec2i& b) {
	return sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2));
}
vec2i Pathfinder::getFarthestTargetPosition() {

	vec2i maxDistTarget = targets.front();
	double maxDist = 0.0f;

	for (const auto& t : targets) {
		double dist = getDistance(start, t);
		if (dist > maxDist) {
			maxDistTarget = t;
			maxDist = dist;
		}
	}

	return maxDistTarget;
}

Pathfinder::Pathfinder(vec2i& start, std::deque<vec2i>& targets, int mapWidth, int mapHeight)
		: start(start), targets(targets), mapWidth(mapWidth), mapHeight(mapHeight) {}

void Pathfinder::discoverMap_BFS(int* map, int* discovered) {

		vec2i target = getFarthestTargetPosition();

		std::queue<vec2i> toCheck;
		toCheck.push(start);

		int targetValue = map[target.y * mapWidth + target.x];

		while (!toCheck.empty()) {

			vec2i current = toCheck.front();
			toCheck.pop();

			if (current == target)
				break;

			for (size_t i = 0; i < 4; i++)
			{
				vec2i exam = current + getDirection(neighborTypes[i]);

				if (isInMap(exam)) {

					int cellValue = map[exam.y * mapWidth + exam.x];
					int distanceFromStart = discovered[current.y * mapWidth + current.x] + 1;

					if ((cellValue == 0 || (cellValue & reverseDirection(neighborTypes[i])) > 0) && cellValue < 16) {
						if (discovered[exam.y * mapWidth + exam.x] == -1) {

							if (cellValue == 0 || exam == target)
								toCheck.push(exam);

							discovered[exam.y * mapWidth + exam.x] = distanceFromStart;
						}
						else if (distanceFromStart < discovered[exam.y * mapWidth + exam.x])
							discovered[exam.y * mapWidth + exam.x] = distanceFromStart;
					}
				}
			}
		}
		finished = true;
	}
void Pathfinder::discoverMap_A_STAR(int* map, int* discovered) {}
int Pathfinder::getSumPathLength(std::deque<vec2i>& targets, int* discovered) {

		if (!finished)
			return 0;

		int sum = 0;

		for (const auto& t : targets)
			sum += discovered[t.y * mapWidth + t.x] - 1;

		return sum;
	}