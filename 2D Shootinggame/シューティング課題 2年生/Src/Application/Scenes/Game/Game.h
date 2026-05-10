#pragma once
//親クラスのインクルード
#include "../SceneBase.h"

//前方宣言
class Player;
class BaseObject;
class Ui;
//class Hit;

enum Wave
{
	WAVE1,
	WAVE2,
	WAVE3,
	WAVE4,
	WAVE5,
};

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


	////全オブジェクトのリストを所得
	//std::vector<std::shared_ptr<BaseObject>> GetObjeList() { return m_ObjList; }


	//オブジェクトリストにオブジェクトを追加
	//void AddObject(std::shared_ptr<BaseObject> obj)
	//{
	//	//リストの末尾に引数で渡された1要素を追加
	//	m_ObjList.push_back(obj);
	//}

	//自機のリストを所得
	std::shared_ptr<Player> GetPlayer() { return m_Player; }

	/*void SetExp(int _exp) { m_Player->SetExp(_exp); }*/


private:

	//ウェーブマネージャー
	void WaveManager();

	bool m_Wave1Flg = false;
	bool m_Wave2Flg = false;
	bool m_Wave3Flg = false;
	bool m_Wave4Flg = false;
	bool m_Wave5Flg = false;

	int m_Wave1Cnt = 0;
	int m_Wave2Cnt = 0;
	int m_Wave3Cnt = 0;
	int m_Wave4Cnt = 0;
	int m_Wave5Cnt = 0;

	Wave m_Wave;

	//自機 //スマートポインタのため、解放する必要がない
	std::shared_ptr<Player> m_Player = nullptr;

	std::shared_ptr<Ui> m_Ui = nullptr;


	//自機画像
	KdTexture m_PlayerTex;


	//背景画像
	KdTexture m_BackTex;

	//背景座標
	static const int BackNum = 2;
	Math::Matrix m_BackMat[BackNum];
	float m_BackPos[BackNum];

	KdTexture m_BackTex2;
	Math::Matrix m_BackMat2;

	int m_BulletCT = 10;
	int m_BulletCnt = 0;


	bool m_BossFlg;

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