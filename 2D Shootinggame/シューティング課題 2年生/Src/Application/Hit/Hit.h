#pragma once

//前方宣言
class EnemyBase;
class Player;

class Hit
{
public :

	Hit() {};

	//初期化
	void Init();

	//敵とプレイヤーの当たり判定
	//敵のインスタンスをアドレスで持って来る(複数の敵を判別するため)
	void EnemyPlayerHit();

	//フラグゲッター
	bool GetFlg() { return m_Flg; }

private:



	//自機と敵の衝突クールタイム
	float m_Cooltime;

	//当たったかどうかの判別フラグ(trueの場合は当たり判定を処理しない)
	bool m_Flg;

	//プレイヤーのスマートポインタ
	std::shared_ptr<Player> m_Player = nullptr;

	//敵のスマートポインタ
	std::shared_ptr<EnemyBase> m_Enemy = nullptr;


public:
	static Hit& GetInstance()
	{
		static Hit instance;
		return instance;
	}
};

#define HIT Hit::GetInstance()