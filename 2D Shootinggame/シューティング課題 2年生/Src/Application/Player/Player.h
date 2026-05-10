#pragma once


enum PlayerColor
{
	RED,
	BLUE
};

class Player
{
public:

	Player() { Init(); }
	~Player() { m_PlusLvTex.Release(); m_PlusBulletTex.Release(); }

	//初期化
	void Init();
	//更新
	void Update();
	//描画
	void Draw();

	//経験値アップデート
	void ExpUpdate();

	//GUI処理
	void ImGuiUpdate();


	//変数ゲッター===========

	//座標ゲッター
	Math::Vector2 GetPos() { return m_Pos; }

	//半径ゲッター
	float GetRadius() { return m_Radius; }

	//ライフゲッター
	int GetHp() { return m_Life; }

	//最大ライフゲッター
	int GetMaxHP() { return m_MaxLife; }

	//攻撃力ゲッター
	int GetAtk() { return m_Atk; }

	//レベルゲッター
	int GetLv() { return m_PlayerLv; }

	//自機生存フラグゲッター
	bool GetPlayerFlg() { return m_Flg; }

	//現在経験値ゲッター
	int GetExp() { return m_PlayerExp; }

	//現在カラーゲッター
	PlayerColor GetColor() { return m_PColor; }

	//弾吸収範囲ゲッター
	float GetBulletAbsorbRange() { return m_BulletAbsorbRange; }

	//============================

	//変数セッター============


	//画像セッター
	void SetTex(KdTexture* tex) { m_Tex = tex; }

	//座標セッター
	void SetPos(Math::Vector2 pos) { m_Pos = pos; }

	//経験値セッター
	void SetExp(int exp) { m_PlayerExp += exp; }

	//透明度セッター
	void SetAlpha(float alpha) { m_Alpha = alpha; }

	//生存フラグセッター
	void SetFlg(float flg) { m_Flg = flg; }

	//切り取り場所セッター
	void SetRect(int rectX, int rectY) { m_RectX = rectX, m_RectY = rectY; }

	//==================

	//自機ステータスアップ関数===

	//攻撃力
	void SetAtk(int atk) { m_Atk += atk; }

	//最大ライフ
	void MaxHPUp(int maxhp) { m_MaxLife += maxhp; }

	//速度
	void SpeedUp(float speed) { m_MovePow += speed; }

	//=============
	

	//被弾処理
	void HitDmg();



private:
	
	//レベル1～9までの弾発射処理
	void Lv1BulletAct();

	//レベル10～19の弾発射処理
	void Lv2BulletAct();

	//レベル20～30の弾発射処理
	void Lv3BulletAct();

	//レベル30～の弾発射処理
	void Lv4BulletAct();

	//自機画像
	KdTexture* m_Tex;

	//座標
	Math::Vector2 m_Pos;

	//移動量
	Math::Vector2 m_Move;

	//移動量
	float m_MovePow;

	///拡大率
	Math::Vector2 m_Scale;

	//合成行列
	Math::Matrix m_Mat;
	//移動行列
	Math::Matrix m_TransMat;
	//拡大行列
	Math::Matrix m_ScaleMat;

	//切り取り範囲
	int m_Rect;

	//アニメーションカウント
	float m_AnimCnt;

	//生存フラグ
	bool m_Flg;

	//半径
	float m_Radius;

	//ライフ
	int m_Life;

	//最大ライフ
	int m_MaxLife;

	//攻撃力
	int m_Atk;

	//自機透明度
	float m_Alpha;

	//現在の経験値量
	int m_PlayerExp;
	int m_PlayerGetExp;

	//現在のレベル
	int m_PlayerLv = 1;

	//次のレベルまでに必要な経験値量
	int m_PlayerNextLvExp = 100;

	//現在の色
	PlayerColor m_PColor;

	//受けるダメージクールタイム====

	//ダメージを受けた後の無敵時間
	const int m_PlayerHitCD = 100;

	//無敵時間カウンター
	int m_PlayerHitCDCnt;

	//点滅処理
	void PlayerHitCDManager();

	//trueなら点滅する
	bool m_BlinkFlg;

	float m_BlinkNum;

	//自機の切り取り場所
	int m_RectX;
	int m_RectY;

	//キーフラグ
	bool m_KeyFlg;

	//デバッグ用レベルアップ
	bool m_LvUpFlg = false;

	//クールタイムマネージャー
	void BulletCntManager();

	//クールタイム(次に打てるまでの時間)
	int m_BulletCT;

	//クールタイムカウンター
	int m_BulletCnt;


	//レベルアップ時の変数

	//弾の速度
	float m_BulletMove;

	//敵の弾の吸収範囲
	float m_BulletAbsorbRange;

	//レベルアップ時======
	KdTexture m_PlusLvTex;

	Math::Vector2 m_PlusLvPos;

	float m_PlusLvAlpha;
	float m_PlusLvCnt;

	Math::Matrix m_PlusLvTransMat;
	Math::Matrix m_PlusLvScaleMat;
	Math::Matrix m_PlusLvMat;


	//弾のレベルアップ時======
	KdTexture m_PlusBulletTex;

	Math::Vector2 m_PlusBulletPos;

	float m_PlusBulletAlpha;
	float m_PlusBulletCnt;

	Math::Matrix m_PlusBulletTransMat;
	Math::Matrix m_PlusBulletScaleMat;
	Math::Matrix m_PlusBulletMat;


	//色変更時
	KdTexture m_ColorChangeTex;

	bool m_CCFlg;

	float m_CCScale;
	float m_CCAlpha;

	int m_CCRect;
	int m_CCRectX;
	int m_CCRectY;

	Math::Matrix m_CCTransMat;
	Math::Matrix m_CCScaleMat;
	Math::Matrix m_CCMat;


public:
	static Player& GetInstance()
	{
		static Player instance;
		return instance;
	}

};