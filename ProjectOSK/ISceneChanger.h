#pragma once

class Scene_Base;
class ISceneChanger
{
public:
	enum
	{
		NOCHANGE,
		SCENE_MENU,
		SCENE_GAME,
	};
public:
	virtual ~ISceneChanger(void){};
	virtual void ChangeScene(int nextScene) = 0;
};

