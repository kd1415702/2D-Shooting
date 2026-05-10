#pragma once

#include"../BaseObject.h"

class Bullet3 : public BaseObject
{
public:

	//コンストラクタ
	Bullet3() {};
	//デストラクタ
	~Bullet3()override { Release(); }

	//初期化
	void Init()override;
	//更新
	void Update()override;
	//描画
	void Draw()override;
	//フラグセッター
	void SetFlg(bool flg)override { m_Flg = flg; }

	//切り取り開始位置セッター
	void SetRect(int x, int y) { m_RectX = x, m_RectY = y; }

	//移動量セッター
	void SetMove(Math::Vector2 _move) { m_Move = _move; }

	//角度セッター
	void SetAngle(float _angle) { m_Angle = _angle; }

private:

	//切り取り開始位置
	int m_RectX;
	int m_RectY;

	//角度
	float m_Angle;

	//回転行列
	Math::Matrix m_RotationMat;

	void Release();
};