#pragma once
//親クラスのインクルード
#include "../SceneBase.h"

//前方宣言
class Player;
class EnemyBase;
class Hit;

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

	void ImGuiUpdate()override;

private:
	
	//自機 //スマートポインタのため、解放する必要がない
	std::shared_ptr<Player> m_Player = nullptr;

	//自機画像
	KdTexture m_PlayerTex;

	//敵
	std::shared_ptr<EnemyBase> m_Enemy = nullptr;

	//当たり判定
	std::shared_ptr<Hit> m_Hit = nullptr;

	//ボタンを押したかどうか
	bool m_KeyFlg = false;

public:
	static Game& GetInstance()
	{
		static Game Ginstance;
		return Ginstance;
	}
};

//ゲーム内の関数アクセス
#define GameAPP Game::GetInstance()