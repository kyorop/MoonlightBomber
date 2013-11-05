#include "EnemyAI.h"
#include "MapState.h"
#include "Enemy.h"
#include "Dijkstra.h"
#include "Search.h"
#include "Route.h"
#include "Target.h"
#include "Avoid.h"
#include "StopRoute.h"
#include "GameConstant.h"
#include "DangerState.h"
#include "DxLib.h"

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

#define BLOCK(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, BLOCK)
#define MAP(i, p, j, q) MapState::GetInstance()->GetState(i+p, j+q, MAP)

EnemyAI::EnemyAI():
	nextState(END),
	currentState(END),
	route(target),
	hasCalculated(0),
	target(new Target),
	avoid(new Avoid),
	stop(new StopRoute),
	search(new Search)
{
}

EnemyAI::~EnemyAI(void)
{
	delete search;
	delete stop;
	delete avoid;
	delete target;
}

int EnemyAI::CheckBombCAroundMyself(const Enemy &myself)
{
	int i_current = myself.GetY() / 32;
	int j_current = myself.GetX() / 32;

	for (int j = j_current; j < GameConst::MAP_LINE; ++j)
	{
		if(MapState::GetInstance()->GetState(i_current, j, MAP) == 1 || MapState::GetInstance()->GetState(i_current, j, BLOCK) == 1)
			break;
		if(MapState::GetInstance()->GetState(i_current, j, BOMB) == 1)
		{
			if(route == target)
			{
				route = stop;
				return 1;
			}
		}
	}
	for (int j = j_current; j >= 0;  --j)
	{
		if(MapState::GetInstance()->GetState(i_current, j, MAP) == 1 || MapState::GetInstance()->GetState(i_current, j, BLOCK) == 1)
			break;
		if(MapState::GetInstance()->GetState(i_current, j, BOMB) == 1)
		{
			if(route == target)
			{
				route = stop;
				return 1;
			}
		}
	}

	for (int i = i_current; i < GameConst::MAP_ROW; ++i)
	{
		if(MapState::GetInstance()->GetState(i, j_current, MAP) == 1 || MapState::GetInstance()->GetState(i, j_current, BLOCK) == 1)
			break;
		if(MapState::GetInstance()->GetState(i, j_current, BOMB) == 1)
		{
			if(route == target)
			{
				route = stop;
				//break;
				return 1;
			}
		}
	}

	for (int i = i_current; i >= 0; --i)
	{
		if(MapState::GetInstance()->GetState(i, j_current, MAP) == 1 || MapState::GetInstance()->GetState(i, j_current, BLOCK) == 1)
			break;
		if(MapState::GetInstance()->GetState(i, j_current, BOMB) == 1)
		{
			if(route == target)
			{
				route = stop;
				//break;
				return 1;
			}
		}
	}

	return 0;
}

int EnemyAI::CheckDanager(const Enemy &myself)
{
	int x_center = (myself.GetX() + myself.GetX() + 32) / 2;
	int y_center = (myself.GetY() + myself.GetY() + 32) / 2;
	//if(MapState::GetInstance()->GetDangerState(myself.GetY()/32, myself.GetX()/32) == 1)
	if(DangerState::GetInstance()->GetDangerState(y_center/32, x_center/32) == 1)
		return 1;
	else
		return 0;
}

int EnemyAI::CheckAbleToMove(const Enemy &myself)
{
	return 0;
}

void EnemyAI::Analyse(int i_current, int j_current, const Enemy &myself)
{
	int x_center = (myself.GetX()*2 + 32) / 2;
	int y_center = (myself.GetY()*2 + 32) / 2;

	//ちょうどマスぴったりにいるときに
	if(myself.GetX() % 32 == 0 && myself.GetY() % 32 == 0)
	{	
		if(CheckDanager(myself) == 1)
		{
			if(currentState != AVOID)
			{
				route = avoid;	//危険地にいるなら逃げる
				nextState = AVOID;
			}
		}
		else if(search->CheckInClosedInterval(y_center/32, x_center/32) == 1 && DangerState::GetInstance()->GetDangerState(y_center/32, x_center/32) == 0)
		{
			if(currentState != STOPTHINKING)
			{
				route = stop;	//閉区間にいるならストップ
				nextState = STOPTHINKING;
			}
		}
		else
		{ 
			if(currentState != TARGET)
			{
				route = target;	//どれでもないならターゲットを狙う
				nextState = TARGET;
			}
		}
	}

	//nextstateがcurrentstateと同じ時は切り替えをしない(今の思考状態でいたい)
	//違うときはnextstateがセットされたということだから、切り替えてほしいということと同値
	if(nextState != currentState)
	{
		currentState = nextState;
		route->DecideGoal(myself);
		route->SetRoute(myself);	
	}
}

int EnemyAI::GetAction(const Enemy &myself)
{
		//ルートがなくなったら思考停止
		if(route->GetRoute(myself) == -1)
		{
			currentState = END;
			nextState = END;
			return STOP;
		}
		else 
		{
			return route->GetRoute(myself);
		}
}


