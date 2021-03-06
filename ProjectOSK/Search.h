#pragma once
#include "GameConstant.h"
#include <list>
#include <vector>
#include <queue>
																													
class Search
{
//各メソッド共用
private:
	int hasVisited[GameConst::MAP_ROW][GameConst::MAP_LINE];
	int count;
	int failed;
//for CheckBomb method
private:
	int checkedOtherRow;
	int checkedOtherLine;
	int success;

private:
	int SetGoal_base(const int i_start, const int j_start, std::vector<int> *i_goal, std::vector<int> *j_goal);
	int CheckAbleToMove(const int i_start, const int j_start, int *const i_safe, int *const j_safe);
	int OnlyCheckAbleToMove(int i_now, int j_now, int i_end, int j_end);
	void SetEscapeRouteToStop(int i_now, int j_now, std::list<int> escapeRoute);
	int CheckAbleToGoTo_base(const int i_start, const int j_start, const int i_goal, const int j_goal);
	int CheckAbleToPass(int i, int j);
public:
	//引数に指定した場所をもとに目的地(ブロックの真横)を決定する
	int SetGoal(const int i_from, const int j_from, std::vector<int> *i_goal, std::vector<int> *j_goal);
	
	//引数に指定した場所をもとに逃げる場所を決定する
	//void CheckAbleToAvoidFromBomb(const int i_from, const int j_from, int *i_safe, int *j_safe);
	
	//引数に指定した場所から爆風範囲に巻き込まれないように他の場所へ移動できるかチェックする
	//移動できるなら１を返す。移動できないなら０を返す。
	//int CheckAbleToMoveInitialized(const int i_start, const int j_start, int *const i_safe, int *const j_safe);
	
	//爆風範囲に入っている時にそこからの最短脱出ルートを提供する
	int SetEscapeRouteWhenInDanger(int i, int j, std::list<int> *escapeRoute);

	
	int CheckAbleToGoTo(int i_start, int j_start, int i_goal, int j_goal);
	//一方向閉区間にいるか調べる。
	//いるなら１を返す。いないなら０を返す。
	int CheckInClosedInterval(int i_now, int j_now);

	Search(void);
	~Search(void);
};

