#include "Player.h"

//初期化
void Player::Init()
{

	m_Pos = { 0,0 };

	m_Scale = { 1,1 };

	m_Flg = true;

	m_Rect = 64;

	m_Radius = m_Rect * m_Scale.x / 2;

	m_MaxLife = 3;

	m_Life = m_MaxLife;

	m_Alpha = 1.0f;

	m_PColor = White;

	m_AnimCnt = 0;

}

void Player::Update()
{
	//上限対策
	//if (m_Life >= m_MaxLife)
	//{
	//	m_Life = m_MaxLife;
	//}

	//座標確定
	m_Pos += m_Move;

	ExpUpdate();

	m_Move = { 0.0f,0.0f };

	//右移動
	if (GetAsyncKeyState('D') & 0x8000)
	{
		m_Move.x += m_MovePow;
	}

	//左移動
	if (GetAsyncKeyState('A') & 0x8000)
	{
		m_Move.x -= m_MovePow;
	}

	//上移動
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_Move.y += m_MovePow;
	}

	//下移動
	if (GetAsyncKeyState('S') & 0x8000)
	{
		m_Move.y -= m_MovePow;
	}

	m_AnimCnt += 0.1f;
	if (m_AnimCnt >= 4)
	{
		m_AnimCnt = 0;
	}

	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
	m_Mat = m_ScaleMat * m_TransMat;

}

void Player::Draw()
{

	if (m_Flg)
	{
		SHADER.m_spriteShader.SetMatrix(m_Mat);
		SHADER.m_spriteShader.DrawTex(m_Tex, Math::Rectangle{ (int)m_AnimCnt * m_Rect,0,m_Rect,m_Rect }, m_Alpha);
	}
}

void Player::ExpUpdate()
{}

void Player::ImGuiUpdate()
{}
