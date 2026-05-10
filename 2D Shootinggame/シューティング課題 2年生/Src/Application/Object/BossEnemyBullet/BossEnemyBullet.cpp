#include "BossEnemyBullet.h"
#include "../../Scenes/SceneManager.h"
#include "../../Player/Player.h"

void BossEnemyBullet::Init()
{
	m_Tex.Load("Assets/Texture/Enemy/Bullet/P1_Bullet_Alt2.png");

	if (rand() % 2 == 0)
	{
		m_Color = RED;
	
	}
	else
	{
		m_Color = BLUE;
	}

	for (auto obj : SceneManager::GetInstance().GetObjList())
	{
		if (obj->GetObjType() == ObjectType::BOSSENEMY)
		{
			m_Pos = obj->GetPos();
		}
	}

	m_Move = { (float)(rand() % 6 - 3), -3.0f};

	m_Flg = true;

	m_Rect = 26;

	m_Scale = { 3.0f,3.0f };

	m_radius = m_Rect * m_Scale.x / 2;

	m_Alpha = 1.0f;

	m_objType = ObjectType::BOSSENEMYBULLET;

	m_Angle = 0;

	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(0, 0, 0);
	m_Mat = m_ScaleMat * m_TransMat;
}

void BossEnemyBullet::Update()
{


	m_Pos += m_Move;
	if (m_Pos.y > 360 || m_Pos.y < -360 || m_Pos.x < -640 || m_Pos.x > 640)
	{

		m_Flg= false;
		

	}


		m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
		m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
		m_RotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_Angle));
		m_Mat = m_ScaleMat * m_RotationMat * m_TransMat;
	

}

void BossEnemyBullet::Draw()
{
	
	if (m_Flg == true)
	{
		if (m_Color == RED)
		{
			SHADER.m_spriteShader.SetMatrix(m_Mat);
			SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,m_Rect / 2,m_Rect }, m_Alpha);
		}
		if (m_Color == BLUE)
		{	
			SHADER.m_spriteShader.SetMatrix(m_Mat);
			SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 13,0,m_Rect / 2,m_Rect }, m_Alpha);
		}
	}
	
	
}

void BossEnemyBullet::Release()
{
	m_Tex.Release();
}
