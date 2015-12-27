﻿#include "DangerState.h"
#include "MapState.h"
#include <iostream>

using namespace BombBombCrash;

DangerState::DangerNode::DangerNode():
	danger(0),
	i_brastCenter(-1),
	j_brastCenter(-1)
{
}

void DangerState::DangerNode::Finalize()
{
	danger = 0;
	i_brastCenter = -1;
	j_brastCenter = -1;
}

DangerState::DangerState(void)
	:node(),
	fireNode()
{
	for (int i = 0; i < BombBombCrash::MAP_ROW; ++i)
	{
		for (int j = 0; j < BombBombCrash::MAP_LINE; ++j)
		{
			fireNode[i][j]= 0;
		}
	}
}


DangerState::~DangerState(void)
{
}


void DangerState::Finalize()
{
	for (int i = 0; i < BombBombCrash::MAP_ROW; ++i)
	{
		for (int j = 0; j < BombBombCrash::MAP_LINE; ++j)
		{
			node[i][j].Finalize();
			fireNode[i][j] = 0;
		}
	}
}


void DangerState::Update()
{
	for (int i = 0; i < BombBombCrash::MAP_ROW; ++i)
	{
		for (int j = 0; j < BombBombCrash::MAP_LINE; ++j)
		{
			//���S���������瑼��S������
			if(node[i][j].danger == 1 && MapState::GetInstance()->GetState(node[i][j].i_brastCenter, node[i][j].j_brastCenter, MapState::BOMB) == 0)
			{
				node[i][j].danger = 0; 
			}
		}
	}

	for (int i = 0; i < BombBombCrash::MAP_ROW; ++i)
	{
		for (int j = 0; j < BombBombCrash::MAP_LINE; ++j)
		{
			if(MapState::GetInstance()->GetState(i, j, MapState::FIRE) == 1)
				fireNode[i][j] = 1;
			else
				fireNode[i][j] = 0;
		}
	}

	for (int i_node= 0; i_node < BombBombCrash::MAP_ROW; ++i_node)
	{
		for (int j_node = 0; j_node < BombBombCrash::MAP_LINE; ++j_node)
		{
			//�{�����u����Ă���Ȃ�
			if(MapState::GetInstance()->GetState(i_node, j_node, MapState::BOMB) == 1)
			{
				int fireLevel = MapState::GetInstance()->GetState(i_node, j_node, MapState::BOMB, 1);
				//�{�����u���ꂽ�ꏊ�͏�ɂP�ɂ��Ă���
				node[i_node][j_node].danger = 1;
				node[i_node][j_node].i_brastCenter = i_node;
				node[i_node][j_node].j_brastCenter = j_node;

				//���S�n�𒆐S�ɉΗ͕������l����댯�n��ɐݒ�

				//���S����E
				for (int i = i_node+1; i <= i_node+fireLevel; ++i)
				{
					if(0 <= i && i < BombBombCrash::MAP_ROW)
					{
						if(MapState::GetInstance()->GetState(i, j_node, MapState::MAP) == 1
							|| MapState::GetInstance()->GetState(i, j_node, MapState::BLOCK) == 1
							||MapState::GetInstance()->GetState(i, j_node, MapState::ITEM) == 1
							||MapState::GetInstance()->GetState(i, j_node, MapState::BOMB) == 1
							//||MapState::GetInstance()->GetState(i, j_node, MapState::CHARACTOR) == 1
							)
						{
							break;
						}
						else
						{
							node[i][j_node].danger = 1;
							node[i][j_node].i_brastCenter = i_node;
							node[i][j_node].j_brastCenter = j_node;
						}
					}
				}

				//���S���獶
				for (int i=i_node-1; i >= i_node - fireLevel ; --i)
				{
					if(0 <= i && i < BombBombCrash::MAP_ROW)
					{
						if(MapState::GetInstance()->GetState(i, j_node, MapState::MAP) == 1
							|| MapState::GetInstance()->GetState(i, j_node, MapState::BLOCK) == 1
							||MapState::GetInstance()->GetState(i, j_node, MapState::ITEM) == 1
							||MapState::GetInstance()->GetState(i, j_node, MapState::BOMB) == 1
							//||MapState::GetInstance()->GetState(i, j_node, MapState::CHARACTOR) == 1
							)
						{
							break;
						}
						else
						{
							node[i][j_node].danger = 1;
							node[i][j_node].i_brastCenter = i_node;
							node[i][j_node].j_brastCenter = j_node;
						}
					}
				}

				//���S���牺
				for (int j=j_node+1; j <= j_node+fireLevel; ++j)
				{
					if(0 <= j && j < BombBombCrash::MAP_LINE)
					{
						if(MapState::GetInstance()->GetState(i_node, j, MapState::MAP) == 1
							|| MapState::GetInstance()->GetState(i_node, j, MapState::BLOCK) == 1
							||MapState::GetInstance()->GetState(i_node, j, MapState::ITEM) == 1
							||MapState::GetInstance()->GetState(i_node, j, MapState::BOMB) == 1
							//||MapState::GetInstance()->GetState(i_node, j, CHARACTOR) == 1
							)
						{
							break;
						}
						else
						{
							node[i_node][j].danger = 1;
							node[i_node][j].i_brastCenter = i_node;
							node[i_node][j].j_brastCenter = j_node;
						}
					}
				}

				//���S�����
				for (int j=j_node-1; j >= j_node - fireLevel ; --j)
				{
					if(0 <= j && j < BombBombCrash::MAP_LINE)
					{
						if(MapState::GetInstance()->GetState(i_node, j, MapState::MAP) == 1
							|| MapState::GetInstance()->GetState(i_node, j, MapState::BLOCK) == 1
							||MapState::GetInstance()->GetState(i_node, j, MapState::ITEM) == 1
							||MapState::GetInstance()->GetState(i_node, j, MapState::BOMB) == 1
							//||MapState::GetInstance()->GetState(i_node, j, CHARACTOR) == 1
							)
						{
							break;
						}
						else
						{
							node[i_node][j].danger = 1;
							node[i_node][j].i_brastCenter = i_node;
							node[i_node][j].j_brastCenter = j_node;
						}
					}
				}
			}
		}
	}
}

int DangerState::GetDangerState(int i , int j)const
{
	if(0 <= i && i < BombBombCrash::MAP_ROW && 0 <= j && j < BombBombCrash::MAP_LINE)
	{
		return node[i][j].danger;
	}
	else
	{
		return -1;
	}
}

int DangerState::GetFireState(int i, int j)const
{
	if(0 <= i && i < BombBombCrash::MAP_ROW && 0 <= j && j < BombBombCrash::MAP_LINE)
	{
		return fireNode[i][j];
	}
	else
	{
		return -1;
	}	
}