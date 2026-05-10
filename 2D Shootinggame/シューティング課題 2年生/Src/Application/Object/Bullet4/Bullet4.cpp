#include "Bullet4.h"
#include "../../Scenes/SceneManager.h"

void Bullet4::Init()
{

	m_Pos = { };
	m_Flg = true;

	m_Angle = 0;

	m_Rect = 30;

	m_Scale = { 2.0f,2.0f };

	m_radius = m_Rect * m_Scale.x / 2;

	m_objType = ObjectType::BULLET;

	m_Tex.Load("Assets/Texture/Bullet/Bullets-0001.png");

	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(0, 0, 0);
	m_Mat = m_ScaleMat * m_TransMat;
}

void Bullet4::Update()
{
	if (m_Flg == true)
	{

		m_Pos += m_Move;

		if (m_Pos.y > 360 || m_Pos.x < -640 || m_Pos.x > 640)
		{
			m_Flg = false;
		}
	}

	//敵との当たり判定
	for (auto obj : SceneManager::GetInstance().GetObjList())
	{
		if (obj->GetObjType() == ObjectType::ENEMY)
		{
			if (obj->GetFlg() == true)
			{
				Math::Vector2 v;
				v = obj->GetPos() - m_Pos;

				if (v.Length() < m_radius + obj->GetRadius())
				{
					m_Flg = false;
					obj->HitDmg(10);

				}
			}
		}
	}

	//ボスエネミーとの当たり判定
	for (auto obj : SceneManager::GetInstance().GetObjList())
	{
		if (obj->GetObjType() == ObjectType::BOSSENEMY)
		{
			if (obj->GetFlg() == true)
			{
				Math::Vector2 v;
				v = obj->GetPos() - m_Pos;
				if (v.Length() < m_radius + obj->GetRadius())
				{
					m_Flg = false;
					obj->HitDmg(10);
				}
			}
		}
	}

	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
	m_RotationMat = Math::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(m_Angle));
	m_Mat = m_ScaleMat * m_RotationMat * m_TransMat;
}


void Bullet4::Draw()
{
	if (m_Flg == true)
	{
		SHADER.m_spriteShader.SetMatrix(m_Mat);
		SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ m_RectX,m_RectY,m_Rect,m_Rect }, 1.0f);
	}
}

void Bullet4::Release()
{
	m_Tex.Release();
}
