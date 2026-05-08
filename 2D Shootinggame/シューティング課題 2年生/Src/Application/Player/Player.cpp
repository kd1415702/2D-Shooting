#include "Player.h"
#include"../Object/Bullet/Bullet.h"
#include"../Object/BaseObject.h"
#include"../Info/Info.h"

#include"../Scenes/SceneManager.h"

//初期化
void Player::Init()
{
	//座標
	m_Pos = { 0.0f,0.0f };

	//移動量
	m_MovePow = 5.0f;

	//拡大率
	m_Scale = { 1.5f,2.0f };

	//生存フラグ
	m_Flg = true;

	//切り取り範囲
	m_Rect = 64;

	//半径
	m_Radius = m_Rect * m_Scale.x / 2.0f;

	//最大ライフ
	m_MaxLife = 3;

	//現在ライフ
	m_Life = m_MaxLife;

	//透明度
	m_Alpha = 1.0f;

	//現在カラー
	m_PColor = RED;

	//点滅
	m_BlinkNum = 0.05;

	//点滅フラグ
	m_BlinkFlg = false;

	//無敵時間カウンター
	m_PlayerHitCDCnt = 0;

	//切り取り場所(横)
	m_RectX = 128;

	//切り取り場所(縦)
	m_RectY = 64;

	//現在カラー
	m_PColor = RED;

	//現在経験値
	m_PlayerExp = 0;

	//キーを押したかどうか
	m_KeyFlg = false;
	
	m_BulletCT = 30;
	m_BulletCnt = 0;
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

		//BulletCntManager();
		m_BulletCnt++;

		//座標確定
		m_Pos += m_Move;


		ExpUpdate();

		m_Move = { 0.0f,0.0f };


		//右移動
		if (GetAsyncKeyState('D') & 0x8000)
		{

			m_Pos.x += 3.0f;
			/*m_Move.x += m_MovePow;*/

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




		if (GetAsyncKeyState('E') & 0x8000)
		{

			if (m_KeyFlg == false)
			{
				m_KeyFlg = true;
			}

		}
		else if (m_KeyFlg == true)
		{
			if (m_PColor == RED)
			{
				m_PColor = BLUE;

				m_RectY = 0;
			}
			else if (m_PColor == BLUE)
			{
				m_PColor = RED;
				m_RectY = 64;
			}
			m_KeyFlg = false;
		}






		m_AnimCnt += 0.1f;
		if (m_AnimCnt >= 4)
		{
			m_AnimCnt = 0;
		}

		//弾発射
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{

			if (m_BulletCnt >= m_BulletCT)
			{

				std::shared_ptr<Bullet> bullet;
				bullet = std::make_shared<Bullet>();


				if (m_PColor == RED)
				{
					bullet->SetRect(70, 80);
				}
				if (m_PColor == BLUE)
				{
					bullet->SetRect(70, 0);
				}

				bullet->Init();
				bullet->SetPos(m_Pos);
				m_BulletCnt = 0;
				SceneManager::GetInstance().AddObject(bullet);
			}
		}



		m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
		m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
		m_Mat = m_ScaleMat * m_TransMat;
	}

}

void Player::Draw()
{
	if (m_Flg)
	{
		SHADER.m_spriteShader.SetMatrix(m_Mat);
		SHADER.m_spriteShader.DrawTex(m_Tex, Math::Rectangle{ m_RectX,m_RectY,m_Rect,m_Rect }, m_Alpha);
	}


}

void Player::ExpUpdate()
{}

void Player::ImGuiUpdate()
{
	ImGui::Text(u8"PlayerLife:%d", m_Life);
	ImGui::Text(u8"PlayerFlg : %d", m_Flg);
	ImGui::Text(u8"EXP : %d", m_PlayerExp);
	ImGui::Text(u8"Color : %d", m_PColor);
	ImGui::Text(u8"Move : %f", m_MovePow);
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
		m_Alpha -= m_BlinkNum;

		if (m_Alpha < 0.5f)
		{
			m_BlinkNum *= -1;
			m_Alpha = 0.5f;
		}
		else if (m_Alpha > 0.9f)
		{
			m_BlinkNum *= -1;
			m_Alpha = 0.9f;
		}
	}
}

void Player::BulletCntManager()
{
	m_BulletCnt++;
}