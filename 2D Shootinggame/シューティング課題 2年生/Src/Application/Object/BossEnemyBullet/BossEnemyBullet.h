#pragma once

#include"../BaseObject.h"

class BossEnemyBullet : public BaseObject
{
public:

	BossEnemyBullet() {};
	~BossEnemyBullet()override { Release(); }

	void Init()override;
	void Update()override;
	void Draw()override;
	
	

private:

	static const int m_BulletNum = 10;

	Math::Vector2 m_Move;

	float m_Angle;



	Math::Matrix m_RotationMat;


	
	void Release();


	//void SetColor(Color _color)
};