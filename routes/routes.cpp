#include <iostream>

#include "Pathfinder.h"

int convertNode(char toTransform) {
	if (toTransform == '-' || toTransform == 'T')
		return 0;
	else if (toTransform < 58)
		return toTransform - 48;

	return toTransform - 55;
}

int main()
{
	int m, n;
    std::cin >> m >> n;

	int* map = new int[n * m];
	int* discovered = new int[n * m];

	std::deque<vec2i>targets;
	vec2i start{0,0};

	for (int yPos = 0; yPos < m; yPos++)
	{
		std::string line;
		std::cin >> line;

		for (int xPos = 0; xPos < n; xPos++)
		{
			map[yPos * n + xPos] = convertNode(line[xPos]);
			discovered[yPos * n + xPos] = -1;

			if (map[yPos * n + xPos] > 0 && map[yPos * n + xPos] < 16)
				targets.push_back({ xPos, yPos });
			else if (line[xPos] == 'T')
				start = { xPos, yPos };
		}
	}
	discovered[start.y * n + start.x] = 0;

	Pathfinder pathfinder(start, targets, n, m);
	pathfinder.discoverMap_BFS(map, discovered);
	std::cout << pathfinder.getSumPathLength(targets, discovered);

	return 0;
}