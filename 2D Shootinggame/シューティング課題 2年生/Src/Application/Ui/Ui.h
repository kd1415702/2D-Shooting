#pragma once

class Player;

class Ui
{
public:

	Ui();
	~Ui() { m_LifeTex.Release(); }

	void Init();
	void Update();
	void Draw();

	void SetPos(Math::Vector2 _pos) { m_LifePos = _pos; }
	void SetRect(int _rect) { m_LifeRect = _rect; }

private:

	//プレイヤーインスタンス
	std::shared_ptr<Player> m_Player = nullptr;

	//ライフ==========

	//画像
	KdTexture m_LifeTex;

	//行列
	Math::Matrix m_LifeTransMat;
	Math::Matrix m_LifeScaleMat;
	Math::Matrix m_LifeMat;

	//座標
	Math::Vector2 m_LifePos;
	//拡大率
	Math::Vector2 m_LifeScale;

	//切り取り範囲
	int m_LifeRect;

	//=======================

	//体力(文字)==================
	KdTexture m_HpTex;
	Math::Matrix m_HpTransMat;
	Math::Matrix m_HpScaleMat;
	Math::Matrix m_HpMat;

	//============================

	//経験値(文字)==================
	KdTexture m_ExpTex;
	Math::Matrix m_ExpTransMat;
	Math::Matrix m_ExpScaleMat;
	Math::Matrix m_ExpMat;

	//============================

	//経験値(バー)==================
	KdTexture m_ExpBarTex;
	Math::Matrix m_ExpBarTransMat;
	Math::Matrix m_ExpBarScaleMat;
	Math::Matrix m_ExpBarMat;

	//============================

};