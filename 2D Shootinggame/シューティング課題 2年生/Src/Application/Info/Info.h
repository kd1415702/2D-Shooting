#pragma once

enum SceneType
{
	TITLE,
	GAME,
	RESULT,
	GAMEOVER
};


class Info
{
public:

	Info();
	~Info();



	static Info& GetInstance()
	{
		static Info instance;
		return instance;
	}
};

#define InfoAPP Info::GetInstance();