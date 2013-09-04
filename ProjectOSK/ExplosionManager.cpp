#include "ExplosionManager.h"
#include "Explosion.h"
#include "Bomb.h"
#include "Player.h"
#include "MapObstacle.h"
#include "ItemManager.h"
#include "DxLib.h"
enum firestate
{
	FIREOFF,
	FIREON,
	EXPLOSION,
};

ExplosionManager::ExplosionManager():
	vex(new std::vector<Explosion*>(5))
{
	//初期火力レベル、中心とその周り一マス
	(*vex)[0] = new Explosion(0,0,0,0);
	(*vex)[1] = new Explosion(1,0,0,0);
	(*vex)[2] = new Explosion(0,1,0,0);
	(*vex)[3] = new Explosion(0,0,1,0);
	(*vex)[4] = new Explosion(0,0,0,1);

	addFireNum = 0;
	nowFireLevel = 1;
}

void ExplosionManager::AddExplosion(const ItemManager &manageItem)
{
	if(manageItem.GetFireState() > this->addFireNum)
	{
		++this->addFireNum;
		++this->nowFireLevel;//次増やすときは、一個隣に増やす

		//一度に4枚増やす(四方に広がるから)
		vex->push_back(new Explosion(this->nowFireLevel,0,0,0));
		vex->push_back(new Explosion(0,this->nowFireLevel,0,0));
		vex->push_back(new Explosion(0,0,this->nowFireLevel,0));
		vex->push_back(new Explosion(0,0,0,this->nowFireLevel));

	}
}

void ExplosionManager::SetExplosion(const Bomb &bomb)
{
	for(int i=0,size=vex->size(); i<size; i++ )
	{
		(*vex)[i]->SetExplosion(bomb);//ボムが置かれ、それが爆発したら、火を存在させる
	}
}

/*
void ExplosionManager::SetZahyou(const Bomb &bomb)
{
	for(int i=0,size=vex->size(); i<size; i++ )
	{
		(*vex)[i]->SetZahyou(bomb);//ボムの置かれた位置から火の座標を定める
	}
}
*/

void ExplosionManager::CheckHitExplosion(Player *player)
{
	//this->explosion.CheckHIt(*player);
	for(int i=0,size=vex->size(); i<size; i++ )
	{
		(*vex)[i]->CheckHItCharactor(player);//プレイヤーとのあたり判定
	}
}

void ExplosionManager::CheckHitObject(MapObstacle *mapobstacle)
{
	const int num = (vex->size() - 1) / 4; //上下左右に広がる火のうち、中心を除く各列の個数
	
	for(int k=1; k<5; k++)//kは初期位置(中心の火のすぐ隣の火); kは4本の爆風を回る
	{
		for(int i=0; i<num; i++)
		{
			(*vex)[k+4*i]->CheckHitObject(mapobstacle);//火は4枚周期

			if( (*vex)[k+4*i]->GetFlag() == FALSE)//一つでも火が壁にぶつかって、
			{
				if(i+1 <= num)//もう次にも火があるなら
				{
					for(int j=i+1; j<num; j++)//その列のそれ以降の火は全部消す
					{
						(*vex)[k+4*j]->SetFlag(FIREOFF);
					}
				}
			continue;//次の火の列に移る
			}
		}//for(i)
	}//for(k)
}

void ExplosionManager::DrawExplosion()
{
	//this->explosion.Draw(map,bomb);
	//if(Timer(1000))
	//{
		for(int i=0,size=vex->size(); i<size; i++ )
		{
			(*vex)[i]->Draw();
		}
	//}
	//else//時間がたったら消す
	//{
	//	for(int i=0,size=vex->size(); i<size; i++ )
	//	{
	//		(*vex)[i]->SetFlag(FALSE);
	//	}
	//}
}

bool ExplosionManager::Timer(int time)
{
	static bool resetTime = true;
	static int startTime;

	if(resetTime == true)
	{
		startTime = GetNowCount();
		resetTime = false;
	}

	if(GetNowCount() - startTime < time)//3秒間はスタート時間をリセットしない
	{
		return TRUE;		//爆弾を表示させる
	}
	else
	{
		resetTime = true;//3秒たったらスタート時間をリセットする
		return FALSE;		//爆弾を消す
	}
}

ExplosionManager::~ExplosionManager(void)
{
	std::vector<Explosion*>::iterator it = vex->begin();

	for(it; it != vex->end(); ++it)
	{
		delete *it;
	}
	delete vex;
}
