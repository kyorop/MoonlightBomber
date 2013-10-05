#pragma once
enum object
{
	MAP,
	BLOCK,
	ITEM,
	CHARACTOR,
	BOMB,
	FIRE,
};

enum dangerState
{
	NODENGER,
	BOMBRANGE
};

class MapState
{
public:
	static const int row = 13;
	static const int line = 17;
private:
	static const int objects = 6;
	static const int topic = 2;
	static int mapState[row][line][objects][topic];
	static dangerState hazardMap[row][line];
private:
	MapState(void);
	MapState(const MapState &ms);
	~MapState(void);
	static void SetState(int x, int y, int object, int state, int option=0);
	void SetDanger(int x, int y, dangerState state);
public:
	static void Initialize();
	static MapState *GetInstance()
	{
		static MapState msInstance;
		return &msInstance;
	}

	//�Z�b�g�n�͂����p����N���X���������W�n�Ȃ̂� x, y �Ŏw�肷��
	//�Q�b�g�n�͂����p����N���X���s��`���ŊǗ����Ă���̂� i, j �Ŏw�肷��
	void SetMapState(int x, int y, int flag, int option=0);
	void SetBlockState(int x, int y, int state, int option=0);
	void SetItemState(int x, int y, int state, int option=0);
	void SetCharactorState(int x, int y, int flag, int option=0);
	void SetBombState(int x, int y, int state, int option=0);
	void SetFireState(int x, int y, int state, int option=0);
	int GetState(int i, int j, int object, int option=0);
	dangerState GetDangerState(int i , int j);
};
