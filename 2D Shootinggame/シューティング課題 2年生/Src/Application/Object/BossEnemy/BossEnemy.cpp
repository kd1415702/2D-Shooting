#include "BossEnemy.h"
#include "../BossEnemyBullet/BossEnemyBullet.h"
#include"../../Scenes/SceneManager.h"

void BossEnemy::Init()
{
	m_Tex.Load("Assets/Texture/BossEnemy/SpaceShip_Boss-0001.png");

	//m_Pos = { 0.0f, 0.0f };

	m_Flg = true;

	m_Rect = 111;

	m_Scale = { 2.0f,2.0f };

	m_radius = m_Rect * m_Scale.x / 2;

	m_MaxHp = 500;

	m_Alpha = 1.0f;

	m_Hp = m_MaxHp;

	m_Rotation = 0.0f;

	m_MoveFlg = false;

	m_BulletCnt = 0;
	m_BulletCT = 5; 

	m_objType = ObjectType::BOSSENEMY;

	m_TransMat = Math::Matrix::CreateTranslation(0, 500, 0);
	m_ScaleMat = Math::Matrix::CreateScale(0, 0, 0);
	m_Mat = m_ScaleMat * m_TransMat;

}

void BossEnemy::Update()
{
	
	if (m_Flg == true)
	{
		m_Rotation += 0.05f;

		if (m_MoveFlg == false)
		{
			if (m_Pos.y < 200)
			{
				m_MoveFlg = true;
				m_Move = { 3.0f,0.0f };
			}
		}

		m_Pos += m_Move;

		//if (m_MoveFlg == true)
		//{
			if (m_Pos.x > 640 - m_radius)
			{
				//m_Pos.x -= 100;
				m_Move.x *= -1.0f;
				return;
			}

			if (m_Pos.x < -640 + m_radius)
			{
				//m_Pos.x += 100;
				m_Move.x *= -1.0f;
				return;
			}
		//}

		

		m_BulletCnt++;

		//弾発射処理
		std::shared_ptr<BossEnemyBullet> bossbullet;
		bossbullet = std::make_shared<BossEnemyBullet>();
		if (rand() % 10 == 1)
		{
			//クールタイムを終えていれば
			if (m_BulletCnt >= m_BulletCT)
			{
				
				bossbullet->Init();
				m_BulletCnt = 0;
				SceneManager::GetInstance().AddObject(bossbullet);
			}
		}


	}

	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
	m_RotationMat = Math::Matrix::CreateRotationZ(m_Rotation);
	m_Mat = m_ScaleMat * m_RotationMat * m_TransMat;
}

void BossEnemy::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,m_Rect,m_Rect }, m_Alpha);
}

void BossEnemy::HitDmg(int _dmg)
{
	m_Hp -= _dmg;
	if (m_Hp <= 0)
	{
		m_Flg = false;


	}
}

void BossEnemy::Release()
{
	m_Tex.Release();
}
