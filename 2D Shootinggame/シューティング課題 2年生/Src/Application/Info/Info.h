#pragma once

enum SceneType
{
	TITLE,
	GAME,
	RESULT,
	GAMEOVER
};


//オブジェクトの種類
enum class ObjectType
{
	NONE,			//タイプ無し
	ENEMY,			//エネミー
	BULLET,			//自機の弾
	BOSSENEMY,		//ボスエネミー
	ENEMYBULLET,	//敵の球
	BOSSENEMYBULLET //ボスエネミーの弾
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