#include "CharacterSet.h"
#include "Charactor.h"
#include "Player.h"
#include "BombManager.h"
#include "BlastManager.h"
#include "BombSetManager.h"

CharacterSet::CharacterSet(Charactor *pCharacter):
	character(pCharacter),
	bomb(new BombSetManager),
	currentSpeed(1),
	currentBombNum(1),
	currentFireLevel(1)
{
}

CharacterSet::~CharacterSet(void)
{
	delete character;
	delete bomb;
}

void CharacterSet::UpdateNumber()
{
	if(currentBombNum < character->GetBombNum())
	{
		bomb->UpNum();
		++currentBombNum;
	}
	if(currentFireLevel < character->GetFireLevel())
	{
		bomb->UpFireLevel();
		++currentFireLevel;
	}
}

void CharacterSet::Set()
{
	if(character->EnableBomb() == 1)//zが押された時
	{
		bomb->Set(character->GetX(), character->GetY());
	}
}

void CharacterSet::Draw()
{
	//この表示の順番が大事だったり…
	bomb->Draw();
	character->Draw();
}

void CharacterSet::Update()
{
	UpdateNumber();
	character->Move();
	character->Register();
	bomb->Update();
	Set();
	
}