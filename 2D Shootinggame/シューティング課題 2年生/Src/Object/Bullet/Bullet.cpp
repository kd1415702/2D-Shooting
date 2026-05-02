#include "Bullet.h"

void Bullet::Init()
{
	m_Pos = {};
	m_Flg = true;
	m_Move = 5.0f;

	m_Rect = 16;

	m_Scale = { 2.0f,2.0f };
}

void Bullet::Update()
{
	m_Pos.y += m_Move;

	if (m_Pos.y > 360)
	{
		m_Flg = false;
	}

	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
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
