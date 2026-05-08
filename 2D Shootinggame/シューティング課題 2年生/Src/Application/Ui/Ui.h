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



};