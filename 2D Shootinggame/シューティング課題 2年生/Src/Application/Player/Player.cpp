#include "Player.h"
#include"../Object/Bullet/Bullet.h"
#include"../Object/Bullet2/Bullet2.h"
#include"..//Object/Bullet3/Bullet3.h"
#include"../Object/Bullet4/Bullet4.h"
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
	m_RectY = 50;

	//現在カラー
	m_PColor = RED;

	//現在経験値
	m_PlayerExp = 0;

	//キーを押したかどうか
	m_KeyFlg = false;
	
	//クールタイム
	m_BulletCT = 30;

	//クールタイムカウンター
	m_BulletCnt = 0;

	//レベル
	m_PlayerLv = 1;

	//レベルアップ時
	m_PlusLvAlpha = 0.0f;
	m_PlusLvCnt = 0;
	m_PlusLvPos = { m_Pos.x + m_Radius, m_Pos.y + m_Radius };

	m_BulletMove = 5.0f;

	m_BulletAbsorbRange = 0.0f;

	m_PlusBulletTex.Load("Assets/Texture/UI/Game/PlusBullet.png");
	m_PlusBulletAlpha = 0.0f;
	m_PlusBulletCnt = 0;


	//色変更時
	m_ColorChangeTex.Load("Assets/Texture/Player/Barrier-0001.png");
	m_CCRect = 88;
	m_CCRectX = 88;
	m_CCRectY = 0;
	m_CCScale = 0;
	m_CCFlg = false;
	m_CCAlpha = 1.0f;


}

void Player::Update()
{
	//上限対策
	if (m_Life >= m_MaxLife)
	{
		m_Life = m_MaxLife;
	}

	//自機が生存していれば
	if (m_Flg)
	{

		//被弾処理
		PlayerHitCDManager();

		//BulletCntManager();
		m_BulletCnt++;

		//座標確定
		m_Pos += m_Move;

		//経験値アップデート
		ExpUpdate();

		m_Move = { 0.0f,0.0f };


		//右移動
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{

			m_Pos.x += m_MovePow;
			if (m_Pos.x >= 1280 / 2 - m_Radius)
			{
				m_Pos.x = 1280 / 2 - m_Radius;
			}

		}


		//左移動
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{

			m_Move.x -= m_MovePow;
			if (m_Pos.x <= -1280 / 2 + m_Radius)
			{
				m_Pos.x = -1280 / 2 + m_Radius;
			}
		}

		//上移動
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{

			m_Move.y += m_MovePow;
			if (m_Pos.y >= 720 / 2 - m_Radius)
			{
				m_Pos.y = 720 / 2 - m_Radius;
			}

		}

		//下移動
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			m_Move.y -= m_MovePow;
			if (m_Pos.y <= -530 / 2 + m_Radius)
			{
				m_Pos.y = -530 / 2 + m_Radius;
			}

		}



		//色変更
		if (GetAsyncKeyState('E') & 0x8000)
		{

			if (m_KeyFlg == false)
			{
				m_KeyFlg = true;
			}

		}
		//キーを離すと発動
		else if (m_KeyFlg == true)
		{
			m_CCFlg = true;
			m_CCAlpha = 1.0f;
			m_CCScale = 0.1f;

			if (m_PColor == RED)
			{
				m_PColor = BLUE;
				m_RectY = 0;

				m_CCRectX = 88;
				m_CCRectY = 0;
			}
			else if (m_PColor == BLUE)
			{
				m_PColor = RED;
				m_RectY = 50;

				m_CCRectX = 88;
				m_CCRectY = 88;
			}
			m_KeyFlg = false;
		}

		if (m_CCFlg == true)
		{
			m_CCScale += 0.1f;
			if (m_CCScale >= 1.5f)
			{
				m_CCAlpha -= 0.1f;
				if (m_CCAlpha <= 0)
				{
					m_CCFlg = false;
				}
			}
		}
		

		//デバッグ用経験値ゲット
		if (GetAsyncKeyState('M') & 0x8000)
		{
			if (m_LvUpFlg == false)
			{
				m_LvUpFlg = true;
			}
		}
		else if(m_LvUpFlg == true)
		{
			m_PlayerExp += 100;
			m_LvUpFlg = false;
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
				if (m_PlayerLv < 10)
				{
					Lv1BulletAct();
				}
				else if (m_PlayerLv >= 10 && m_PlayerLv < 20)
				{
					Lv2BulletAct();
				}
				else if (m_PlayerLv >= 20 && m_PlayerLv < 30)
				{
					Lv3BulletAct();
				}
				else if (m_PlayerLv >= 30)
				{
					Lv4BulletAct();
				}
			}
		}


		m_PlusLvPos = { m_Pos.x + m_Radius + 50, m_Pos.y + m_Radius };

		m_PlusBulletPos = { m_Pos.x + m_Radius + 50, m_Pos.y };

		//レベルアップ時の処理
		if (m_PlusLvCnt > 0)
		{
			m_PlusLvCnt--;
			m_PlusLvAlpha -= 0.01f;

			m_Pos.y += 0.3f;
		}
		else
		{
			m_PlusLvAlpha = 0.0f;
		}

		if (m_PlusBulletCnt > 0)
		{
			m_PlusBulletCnt--;
			m_PlusBulletAlpha -= 0.01f;

			m_Pos.y += 0.3f;
		}
		else
		{
			m_PlusBulletAlpha = 0.0f;
		}

		
	}

	m_PlusLvTransMat = Math::Matrix::CreateTranslation(m_PlusLvPos.x, m_PlusLvPos.y, 0);
	m_PlusLvScaleMat = Math::Matrix::CreateScale(1.0f, 1.0f, 0);
	m_PlusLvMat = m_PlusLvScaleMat * m_PlusLvTransMat;

	m_PlusBulletTransMat = Math::Matrix::CreateTranslation(m_PlusBulletPos.x, m_PlusBulletPos.y, 0);
	m_PlusBulletScaleMat = Math::Matrix::CreateScale(1.2f, 1.2f, 0);
	m_PlusBulletMat = m_PlusBulletScaleMat * m_PlusBulletTransMat;

	m_CCTransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_CCScaleMat = Math::Matrix::CreateScale(m_CCScale, m_CCScale, 0);
	m_CCMat = m_CCScaleMat * m_CCTransMat;


	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
	m_Mat = m_ScaleMat * m_TransMat;

}


void Player::Draw()
{
	if (m_Flg)
	{
		//自機
		SHADER.m_spriteShader.SetMatrix(m_Mat);
		SHADER.m_spriteShader.DrawTex(m_Tex, Math::Rectangle{ m_RectX,m_RectY,m_Rect,43 }, m_Alpha);

		if (m_CCFlg == true)
		{
			//色変更アニメーション
			SHADER.m_spriteShader.SetMatrix(m_CCMat);
			SHADER.m_spriteShader.DrawTex(&m_ColorChangeTex, Math::Rectangle{ m_CCRectX,m_CCRectY,m_CCRect,m_CCRect }, m_CCAlpha);
		}
		//レベルアップ時画像
		SHADER.m_spriteShader.SetMatrix(m_PlusLvMat);
		SHADER.m_spriteShader.DrawTex(&m_PlusLvTex, Math::Rectangle{ 0,0,200,60 }, m_PlusLvAlpha);

		//弾レベルアップ時画像
		SHADER.m_spriteShader.SetMatrix(m_PlusBulletMat);
		SHADER.m_spriteShader.DrawTex(&m_PlusBulletTex, Math::Rectangle{ 0,0,200,60 }, m_PlusBulletAlpha);
	}


}

//経験値アップデート
void Player::ExpUpdate()
{
	//上限
	if (m_PlayerLv > 99)
	{
		m_PlayerLv = 99;
	}


	//現在経験値が次のレベルまでに必要な経験値を超えていれば
	if (m_PlayerExp >= m_PlayerNextLvExp)
	{
		//レベルアップ
		m_PlayerLv++;

		//現在経験値をリセット
		m_PlayerExp = 0;

		//レベルアップ時処理
		m_PlusLvCnt = 90;
		m_PlusLvAlpha = 1.0f;

		//レベルが40以下の時
		if (m_PlayerLv < 40)
		{
			//レベルが10の倍数のとき
			if (m_PlayerLv % 10 == 0)
			{

				m_PlusBulletCnt = 90;
				m_PlusBulletAlpha = 1.0f;
				m_Life++;
			}
		}

		//3通りからランダムでステータスアップ
		switch (rand() % 3)
		{
		//弾速度アップ
		case 0:
		{
			m_BulletMove += 1.0f;
			m_PlusLvTex.Load("Assets/Texture/UI/Game/BulletSpeed_transparent.png");
			break;
		}
		//打てる頻度アップ
		case 1:
		{
			if (m_BulletCT <= 10)
			{
				m_BulletCT -= 2;
				m_PlusLvTex.Load("Assets/Texture/UI/Game/BulletCT_transparent.png");
				break;
			}
		}
		//敵の弾の吸収範囲アップ
		case 2:
		{
			m_BulletAbsorbRange += 8.0f;
			m_PlusLvTex.Load("Assets/Texture/UI/Game/AbsorbRange_transparent.png");
			break;
		}
		default:
			break;
		}
	}
}



void Player::ImGuiUpdate()
{
	ImGui::Text(u8"BulletMove : %f", m_BulletMove);
	ImGui::Text(u8"BulletCT : %d", m_BulletCT);
	ImGui::Text(u8"BulletAbsorbRange : %f", m_BulletAbsorbRange);
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

		//発表用
		if (m_Life <= 0)
		{
			m_Life = 1;

		}

		//if (m_Life <= 0)
		//{
		//	m_Life = 0;

		//	m_Flg = false;
		//	
		//}

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

void Player::Lv1BulletAct()
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
	bullet->SetMove({ 0.0f, m_BulletMove });
	m_BulletCnt = 0;
	SceneManager::GetInstance().AddObject(bullet);
}

void Player::Lv2BulletAct()
{
	std::shared_ptr<Bullet2> bullet2;
	bullet2 = std::make_shared<Bullet2>();

	if (m_PColor == RED)
	{
		bullet2->SetRect(70, 80);
	}
	if (m_PColor == BLUE)
	{
		bullet2->SetRect(70, 0);
	}

	
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

	//2発同時に出す
	bullet->Init();
	bullet->SetPos({m_Pos.x - 30.0f, m_Pos.y});
	bullet->SetMove({ 0.0f, m_BulletMove });
	SceneManager::GetInstance().AddObject(bullet);

	bullet2->Init();
	bullet2->SetPos({ m_Pos.x + 30.0f, m_Pos.y });
	bullet2->SetMove({ 0.0f, m_BulletMove });
	SceneManager::GetInstance().AddObject(bullet2);


	m_BulletCnt = 0;
	
}

void Player::Lv3BulletAct()
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

	std::shared_ptr<Bullet2> bullet2;
	bullet2 = std::make_shared<Bullet2>();

	if (m_PColor == RED)
	{
		bullet2->SetRect(70, 80);
	}
	if (m_PColor == BLUE)
	{
		bullet2->SetRect(70, 0);
	}

	std::shared_ptr<Bullet3> bullet3;
	bullet3 = std::make_shared<Bullet3>();

	if (m_PColor == RED)
	{
		bullet3->SetRect(70, 80);
	}
	if (m_PColor == BLUE)
	{
		bullet3->SetRect(70, 0);
	}
	
	bullet->Init();
	bullet->SetPos({ m_Pos.x, m_Pos.y });
	bullet->SetMove({ 0.0f, m_BulletMove });
	SceneManager::GetInstance().AddObject(bullet);

	bullet2->Init();
	bullet2->SetPos({ m_Pos.x, m_Pos.y });
	bullet2->SetMove({ -m_BulletMove, m_BulletMove });
	bullet2->SetAngle(20.0f);
	SceneManager::GetInstance().AddObject(bullet2);

	bullet3->Init();
	bullet3->SetPos({ m_Pos.x, m_Pos.y });
	bullet3->SetMove({ m_BulletMove, m_BulletMove });
	bullet3->SetAngle(-30.0f);
	SceneManager::GetInstance().AddObject(bullet3);

	m_BulletCnt = 0;
}

void Player::Lv4BulletAct()
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

	std::shared_ptr<Bullet2> bullet2;
	bullet2 = std::make_shared<Bullet2>();

	if (m_PColor == RED)
	{
		bullet2->SetRect(70, 80);
	}
	if (m_PColor == BLUE)
	{
		bullet2->SetRect(70, 0);
	}

	std::shared_ptr<Bullet3> bullet3;
	bullet3 = std::make_shared<Bullet3>();

	if (m_PColor == RED)
	{
		bullet3->SetRect(70, 80);
	}
	if (m_PColor == BLUE)
	{
		bullet3->SetRect(70, 0);
	}

	std::shared_ptr<Bullet4> bullet4;
	bullet4 = std::make_shared<Bullet4>();

	if (m_PColor == RED)
	{
		bullet4->SetRect(70, 80);
	}
	if (m_PColor == BLUE)
	{
		bullet4->SetRect(70, 0);
	}

	bullet->Init();
	bullet->SetPos({ m_Pos.x + 30.0f, m_Pos.y });
	bullet->SetMove({ 0.0f, m_BulletMove });
	SceneManager::GetInstance().AddObject(bullet);

	bullet2->Init();
	bullet2->SetPos({ m_Pos.x - 30.0f, m_Pos.y });
	bullet2->SetMove({ 0.0f, m_BulletMove });
	SceneManager::GetInstance().AddObject(bullet2);

	bullet3->Init();
	bullet3->SetPos({ m_Pos.x, m_Pos.y });
	bullet3->SetMove({ -m_BulletMove, m_BulletMove });
	bullet3->SetAngle(20.0f);
	SceneManager::GetInstance().AddObject(bullet3);

	bullet4->Init();
	bullet4->SetPos({ m_Pos.x, m_Pos.y });
	bullet4->SetMove({ m_BulletMove, m_BulletMove });
	bullet4->SetAngle(-20.0f);
	SceneManager::GetInstance().AddObject(bullet4);

	m_BulletCnt = 0;
}
