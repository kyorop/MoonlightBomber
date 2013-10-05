#pragma once
#include "Dijkstra.h"
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include "GameConstant.h"
#include <vector>
#define MAPSIZE_X 17
#define MAPSIZE_Y 13

class Enemy;
class EnemyAI
{
private:
	
public:
	//���ʗ��p
	int visited[GameConst::MAP_ROW][GameConst::MAP_LINE];
	int hasVisited[GameConst::MAP_ROW][GameConst::MAP_LINE];
	int success;
	int checkedOtherRow;
	int checkedOtherLine;
	Dijkstra *dijkstra;

	//�����ڕW���[�g
	std::list<int> targetRoute;
	//�Z���댯������[�g
	std::list<int> noDengerRoute;

public:
	std::queue<int> que_i;
	std::queue<int> que_j;

	void Initialize();
	void SetGoal(const int i, const int j);
	//void SetRoute(const int i, const int j, const int goal_i, const int goal_j);
	int i_safe;
	int j_safe;
	//int CheckAbleToEscapeFromBomb(const int i, const int j);
	int CheckAbleToMove(const int i_now, const int j_now);
	void CheckAbleToEscapeFromBomb(const int i, const int j);
	int rand;

	//�~�܂�K�v������Ȃ�0��Ԃ�
	int CheckBomb(const int i_start, const int j_start);
	void Analyse(int i_current, int j_current, Enemy *myself);
	std::vector<int> i_goal;
	std::vector<int> j_goal;
	std::vector<int> route;
	int GetAction(int next);
	EnemyAI();
	~EnemyAI(void);
};
