#pragma once

enum SceneType
{
	TITLE,
	GAME,
	RESULT,
	GAMEOVER
};

enum PlayerColor
{
	Black,
	White
};

class Info
{
public:

	Info();
	~Info();

	//現在の状態(自機)
	PlayerColor m_PColor;

	static Info& GetInstance()
	{
		static Info instance;
		return instance;
	}
};

#define InfoAPP Info::GetInstance();