#pragma once
namespace BombBombCrash
{
	class Timer
	{
		int count;
		bool reset;
		int startTime;
		int limitedTime;
		static const int frameTime = 16;
	public:
		//呼び出されてから引数指定ミリ秒がたったらTRUEを返す
		bool CountDownFrame(int millisecond);
		bool CountDownRealTime(int millisecond);
		Timer(void);
		~Timer(void);
		void TurnReset(void);
		int GetLeftedRealTime()const;
	};
}




