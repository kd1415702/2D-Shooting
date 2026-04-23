#pragma once
//親クラスのインクルード
#include "../SceneBase.h"

class Game : public SceneBase
{
public:

	Game() {};
	~Game() {};

	void Init()override;
	void Update()override;
	void Draw()override;



public:
	static Game& GetInstance()
	{
		static Game Ginstance;
		return Ginstance;
	}
};

//ゲーム内の関数アクセス
#define GameAPP Game::GetInstance()