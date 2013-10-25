#pragma once
#include <vector>
#include <list>

class ICollisionable;

//シングルトン
class Collision
{
private:
	std::vector<ICollisionable*> disableGoingThrough;
	std::vector<ICollisionable*> bomb;
	std::vector<ICollisionable*> character;
	std::list<ICollisionable*> block;
	std::list<ICollisionable*> map;

	static const int degreeOfHit = 5;
	static const int haba = 16;
private:
	Collision(void);
	Collision(const Collision &collision);

	//通れない系
	void CheckEnbleToStop();
	//通常のあたり判定
	void CheckOneUponAnother();
	//火との接触判定
	void CheckCollisionWithFire();
public:
	~Collision(void);
	static Collision* GetInstance();
	void RegiPlayer(ICollisionable *player);
	//void RegisterWithBomb(ICollisionable *bomb);
	//void RegisterWithCharactor(ICollisionable *charactor);
	void Register(ICollisionable *anythingCollisionable);
	void CheckCollision();
};

