#pragma once

#include"../BaseObject.h"

class Bullet2 : public BaseObject
{
public:

	//コンストラクタ
	Bullet2() {};
	//デストラクタ
	~Bullet2()override { Release(); }

	//初期化
	void Init()override;
	//更新
	void Update()override;
	//描画
	void Draw()override;
	//フラグセッター
	void SetFlg(bool flg)override { m_Flg = flg; }

	void SetRect(int x, int y) { m_RectX = x, m_RectY = y; }

	void SetMove(Math::Vector2 _move) { m_Move = _move; }

	void SetAngle(float _angle) { m_Angle = _angle; }

private:


	//切り取り開始位置
	int m_RectX;
	int m_RectY;

	//角度
	float m_Angle;

	Math::Matrix m_RotationMat;

	void Release();

};