#pragma once
#include "route.h"
#include <vector>
#include <list>

class Search;
class Dijkstra;
class Target :
	public Route
{
private:
enum
{
	END = -1,
	STOP,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BOMBSET,
	BOMBSETOFF,
};
private:
	std::vector<int> i_to;
	std::vector<int> j_to;
	int rand;
	std::list<int> routeList;

	Search *const search;
	Dijkstra *const dijkstra;

	int hasCalculated;
	int x_next;
	int y_next;

public:
	void DecideGoal(const Enemy &myself);
	void SetRoute(const Enemy &myself);
	int GetRoute(const Enemy &myself);
	Target(void);
	~Target(void);
};
