#include "Scene_Menu.h"

#include "ISceneChanger.h"
#include "Scene_Game.h"
#include "DxLib.h"

Scene_Menu::Scene_Menu()
{
}


Scene_Menu::~Scene_Menu(void)
{
}


void Scene_Menu::UpdateScene()
{
	if(CheckHitKey(KEY_INPUT_RETURN) == 1)
	{
		sceneMrg->ChangeScene(new Scene_Game);
	}
}

void Scene_Menu::Update(void)
{
	UpdateScene();
}


void Scene_Menu::Draw(void)
{
	int deepskyblue = GetColor(0, 191, 255);
	DrawFormatString(10, 10, deepskyblue,"ゲームを始めるにはエンターキーを押してね！");
}