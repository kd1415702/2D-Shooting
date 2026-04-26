#pragma once
//親クラスのインクルード
#include "../SceneBase.h"

//前方宣言
class Player;

//ゲーム画面を管理するクラス
class Game : public SceneBase
{
public:

	Game() {};
	~Game() { Release(); };

	void Init()override;
	void Update()override;
	void Draw()override;

	void Release();

private:
	
	//自機 //スマートポインタのため、解放する必要がない
	std::shared_ptr<Player> m_Player;
	/*Player* m_Player;*/

	//自機画像
	KdTexture m_PlayerTex;

public:
	static Game& GetInstance()
	{
		static Game Ginstance;
		return Ginstance;
	}
};

//ゲーム内の関数アクセス
#define GameAPP Game::GetInstance()