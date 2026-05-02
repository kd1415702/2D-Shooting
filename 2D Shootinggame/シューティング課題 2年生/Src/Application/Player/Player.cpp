#include "Player.h"


//初期化
void Player::Init()
{

	m_Pos = { 0,0 };

	m_Scale = { 1,1 };

	m_Flg = true;

	m_Rect = 64;

	m_Radius = m_Rect * m_Scale.x / 2.0f;

	m_MaxLife = 3;

	m_Life = m_MaxLife;

	m_Alpha = 1.0f;

	m_PColor = White;

	m_AnimCnt = 0;

	BlinkNum = 0.05;

	m_BlinkFlg = false;

	m_PlayerHitCDCnt = 0;

}

void Player::Update()
{
	//上限対策
	//if (m_Life >= m_MaxLife)
	//{
	//	m_Life = m_MaxLife;
	//}

	//自機が生存していれば
	if (m_Flg)
	{
	

		PlayerHitCDManager();

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


		//if (m_Enemy->GetFlg())
		//{
		//	const float x = m_Enemy->GetPos().x - m_Pos.x;
		//	const float y = m_Enemy->GetPos().y - m_Pos.y;
		//	const float z = sqrt(x * x + y * y);



		//	//半径＋半径
		//	const float sum = m_Enemy->GetRadius() + m_Radius;

		//	if (z < sum)
		//	{

		//		HitDmg();

		//		return;
		//	}
		//}











		m_AnimCnt += 0.1f;
		if (m_AnimCnt >= 4)
		{
			m_AnimCnt = 0;
		}


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
{
	ImGui::Text(u8"PlayerLife:%d", m_Life);
	ImGui::Text(u8"PlayerFlg : %d", m_Flg);
}

void Player::HitDmg()
{
	if (m_PlayerHitCDCnt >= m_PlayerHitCD)
	{
		m_BlinkFlg = true;
		m_Life--;
		m_PlayerHitCDCnt = 0;
		m_Alpha = 0.5f;
		//ここに音

		if (m_Life <= 0)
		{
			m_Life = 0;

			m_Flg = false;
		}

	}
}

void Player::PlayerHitCDManager()
{
	m_PlayerHitCDCnt++;

	if (m_PlayerHitCDCnt >= m_PlayerHitCD)
	{
		m_Alpha = 1.0f;
		m_BlinkFlg = false;
	}

	//点滅処理
	if (m_BlinkFlg)
	{
		m_Alpha -= BlinkNum;

		if (m_Alpha < 0.5f)
		{
			BlinkNum *= -1;
			m_Alpha = 0.5f;
		}
		else if (m_Alpha > 0.9f)
		{
			BlinkNum *= -1;
			m_Alpha = 0.9f;
		}
	}
}
