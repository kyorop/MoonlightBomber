#pragma once
#include "IDrawable.h"
#include "IRegister.h"
#include <vector>

class ExplosionManager;
class BombManager;
class MapObstacle;
class Player;
class ItemManager;
class Charactor;
class Bomb;
class BlastManager:
	virtual public IDrawable, virtual public IRegister
{
private:
	int nowBlastNum;
public:
	void FireLevelUp();
	void Add();
	void Set(int index, int x, int y);
	void Maintain();
	void Draw();
	void Register();
	BlastManager(void);
	~BlastManager(void);


	std::vector<ExplosionManager*> blast;
	
};

