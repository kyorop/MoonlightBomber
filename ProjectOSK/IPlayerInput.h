#pragma once

class IPlayerInput
{
public:
	virtual ~IPlayerInput(){}

	virtual bool GetInputMoveUp() = 0;
	virtual bool GetInputMoveRight() = 0;
	virtual bool GetInputMoveDown() = 0;
	virtual bool GetInputMoveLeft() = 0;
	virtual bool GetInputPutBomb() = 0;
};