#pragma once

class Key
{
private:
	int key[256];
public:
	int CheckOnePushKey(int keyCode);
	Key(void);
	~Key(void);
};

