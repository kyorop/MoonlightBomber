#include "Enemy.h"
#include "Player.h"
#include "MapState.h"
#include "DxLib.h"
#define MV 1
#define HABA 10

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


Enemy::Enemy(int x, int y):
	nowStop(0),
	AI(),
	nextAction(0),
	//moveNow(0),
	exploration(0),
	muki(STOP),
	bombSet(0)
{
	this->mv = MV;
	this->flag = TRUE;
	LoadDivGraph("redbombman.png", 20, 4, 5, 32, 32, this->graph, FALSE);
	this->x = x;
	this->y = y;
	this->resetRoutine = 1;
}

Enemy::~Enemy(void)
{
}

int Enemy::CheckAbleBombSet()
{
	return 0;
}

void Enemy::Order()
{
	if(exploration == 0)
	{
		AI.Analyse(this->y/32, this->x/32, this);
		exploration = 1;
		nextAction = 0;
	}
}

void Enemy::Move(int g_lastTime)
{
	if(exploration == 1 && nowStop == 0)
	{
		switch(AI.GetAction(nextAction))
		{
		case STOP:
			nowStop = 1;
			break;
		case UP:
			this->muki = UP;
			this->y -= this->mv;
			break;
		case DOWN:
			this->muki = DOWN;
			this->y += this->mv;
			break;
		case LEFT:
			this->muki = LEFT;
			this->x -= this->mv;
			break;
		case RIGHT:
			this->muki = RIGHT;
			this->x += this->mv;
			break;
		case BOMBSET:
			this->bombSet = 1;
			break;
		case BOMBSETOFF:
			this->bombSet = 0;
			break;
		case -1:
			exploration = 0;
			break;
		}

		//nextAction = 0;
		
		if(this->x % 32 == 0 && this->y % 32 == 0)
		{
			++nextAction;
		}
		
		if(this->x < 64)this->x = 64;
		if(this->x > 32*14)this->x = 32*14;
		if(this->y < 32)this->y = 32;
		if(this->y > 32*11)this->y = 32*11;

		this->rx = this->x+32;
		this->dy = this->y+32;

	}//end of if(exploration == 1 && nowStop == 0)

	this->animpat = (g_lastTime / (1000 / 12)) % 4;
}

void Enemy::Draw(void)
{
	switch(this->muki)
	{
	case STOP:
		DrawGraph(this->x, this->y, this->graph[4], TRUE);break;
	case LEFT:
		DrawGraph(this->x, this->y, this->graph[animpat+8], TRUE);break;
	case RIGHT:
		DrawGraph(this->x, this->y, this->graph[animpat+12], TRUE);break;
	case UP:
		DrawGraph(this->x, this->y, this->graph[animpat+0], TRUE);break;
	case DOWN:
		DrawGraph(this->x, this->y, this->graph[animpat+4], TRUE);	break;
	}
}

int Enemy::GetBombSet(void)const
{
	return this->bombSet;
}



void Enemy::CancelStop(void)
{
	if(nowStop == 1)
	{
		nowStop = 0;
	}
}