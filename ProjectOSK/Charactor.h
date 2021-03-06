#pragma once
#include "IRegister.h"
#include "IDrawable.h"
#include "MapObject.h"

class Map;
class Charactor
	:public IRegister,
	public IDrawable,
	public MapObject
{
protected:
	int preX;
	int preY;
	int mv;//スピード
	int bombNum;//出せるボムの個数
	int fireLevel;//中心からの火のマス数(中心は含めない)
	const int id;
	static int idGenerator;
public:
	Charactor(void);
	virtual ~Charactor(void);

	//virtual void SetCharactorState(int flag);
	int GetBombNum()const;
	int GetFireLevel()const;
	int GetMV()const;
	void AddBombNum();
	void AddFireLevel();
	virtual void AddMV() = 0;
	virtual void Move() = 0;
	virtual void Draw() = 0;
	virtual int EnableBomb()const = 0;
	void Register();
};

