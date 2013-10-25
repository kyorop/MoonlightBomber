#pragma once
#include "ICollisionable.h"

class MapObject
	:public ICollisionable
{
protected:
	int x;
	int rx;
	int y;
	int dy;
	int flag;

public:
	MapObject(void);
	virtual ~MapObject(void);

	virtual int GetX()const;
	virtual void SetX(int x);
	virtual int GetRX()const;
	virtual int GetY()const;
	virtual void SetY(int y);
	virtual int GetDY()const;
	virtual int GetFlag()const;
	virtual void SetFlag(int flag);

};

