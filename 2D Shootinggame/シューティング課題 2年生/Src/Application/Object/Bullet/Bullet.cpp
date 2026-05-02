#include "Bullet.h"
#include "../../Scenes/Game/Game.h"

void Bullet::Init()
{
	

	m_Pos = {};
	m_Flg = true;
	m_Move = { 5.0f,5.0f };

	m_Rect = 16;

	m_Scale = { 2.0f,2.0f };

	m_objType = ObjectType::BULLET;
}

void Bullet::Update()
{
	m_Pos.y += m_Move.y;

	if (m_Pos.y > 360)
	{
		m_Flg = false;
	}

	
	for (auto obj : m_owner->GetObjeList())
	{
		if (obj->GetObjType() == ObjectType::ENEMY)
		{
			Math::Vector2 v;
			v = obj->GetPos() - m_Pos;

			if (v.Length() < 64.0f)
			{
				obj->Hit();
			}
		}
	}



	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
	m_Mat = m_ScaleMat * m_TransMat;
}

void Bullet::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_Mat);
	SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,m_Rect,m_Rect }, 1.0f);
}

void Bullet::Release()
{
	m_Tex.Release();
}
