#pragma once
#include "GameConstant.h"

class DangerState
{
private:
	struct DangerNode
	{
	public:
		int danger;
		int i_brastCenter;
		int j_brastCenter;
	public:
		DangerNode();
		void Finalize();
	};

public:
	DangerNode node[GameConst::MAP_ROW][GameConst::MAP_LINE];
	int fireNode[GameConst::MAP_ROW][GameConst::MAP_LINE];
private:
	DangerState(void);
	DangerState(const DangerState &ds);
	~DangerState(void);
public:
	static DangerState *GetInstance()
	{
		static DangerState dsInstance;
		return &dsInstance;
	}
	
	void Finalize();
	void Update();
	int GetDangerState(int i, int j)const;
	int GetFireState(int i, int j)const;
};

