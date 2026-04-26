#pragma once

enum PlayerColor
{
	Black,
	White
};

class Player
{
public:

	Player() { Init(); }
	~Player() {};

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

	//============================

	//変数セッター============


	//画像セッター
	void SetTex(KdTexture* tex) { m_Tex = tex; }

	//座標セッター
	void SetPos(Math::Vector2 pos) { m_Pos = pos; }

	//経験値セッター
	void SetExp(int exp);

	//透明度セッター
	void SetAlpha(float alpha) { m_Alpha = alpha; }

	void SetFlg(float flg) { m_Flg = flg; }

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
	void HitDmg(float dmg);

	

private:

	//自機画像
	KdTexture* m_Tex;

	//座標
	Math::Vector2 m_Pos;

	//移動量
	Math::Vector2 m_Move;

	//移動量
	float m_MovePow = 5.0f;

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

	//無敵時間
	float m_Invisible;

	//自機透明度
	float m_Alpha;

	//現在の経験値量
	int m_PlayerExp;
	int m_PlayerGetExp;

	//現在のレベル
	int m_PlayerLv;

	//次のレベルまでに必要な経験値量
	int m_PlayerNextLvExp;

	PlayerColor m_PColor;

};