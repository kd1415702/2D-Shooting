#pragma once

#include"../BaseObject.h"

class BossEnemy : public BaseObject
{
public:

	BossEnemy() {};
	~BossEnemy()override { Release(); }
	void Init()override;
	void Update()override;
	void Draw()override;

	void HitDmg(int _dmg)override;

private:

	Math::Matrix m_RotationMat;
	
	float m_Rotation;

	bool m_MoveFlg;

	void Release();

	int m_BulletCnt;
	int m_BulletCT;
};