#pragma once
//親クラスのインクルード
#include "../SceneBase.h"

//前方宣言
class Player;
class BaseObject;
//class Hit;

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

	void PreUpdate();

	//全オブジェクトのリストを所得
	std::vector<std::shared_ptr<BaseObject>> GetObjeList() { return m_ObjList; }


	//オブジェクトリストにオブジェクトを追加
	void AddObject(std::shared_ptr<BaseObject> obj)
	{
		//リストの末尾に引数で渡された1要素を追加
		m_ObjList.push_back(obj);
	}

private:

	//弾発射
	void BulletAct();

	//クールタイムマネージャー
	void m_BulletCntManager();

	//クールタイム(次に打てるまでの時間)
	const int m_BulletCT = 10;

	//クールタイムカウンター
	int m_BulletCnt;
	
	//自機 //スマートポインタのため、解放する必要がない
	std::shared_ptr<Player> m_Player = nullptr;

	//自機画像
	KdTexture m_PlayerTex;

	//全オブジェクトを可変長配列で管理
	std::vector<std::shared_ptr<BaseObject>> m_ObjList;


	////敵
	//std::shared_ptr<EnemyBase> m_Enemy = nullptr;

	////弾
	//std::shared_ptr<Bullet> m_Bullet = nullptr;

	/*std::vector<std::shared_ptr<EnemyBase>*/

	////当たり判定
	//std::shared_ptr<Hit> m_Hit = nullptr;

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