#include "Enemy.h"
#include "../EnemyBullet/EnemyBullet.h"
#include"../../Scenes/SceneManager.h"

//初期化
void Enemy::Init()
{

		float x = rand() % 1000 - 500 + 1;

		//座標
		m_Pos = { x,200.0f };

		//透明度
		m_Alpha = 1.0f;


		//移動量
		m_Move = { 4.0f,0 };

		//生存フラグ
		m_Flg = true;

		if (rand() % 2 == 0)
		{
			//画像ロード
			//赤画像
			m_Tex.Load("Assets/Texture/Enemy/spr_spaceship_05_animation.png");

			//切り取り範囲
			m_Rect = 24;

			//色
			m_Color = RED;

			//拡大率
			m_Scale = { 3.0f,3.0f };
		}
		else
		{
			//青画像
			m_Tex.Load("Assets/Texture/Enemy/spr_spaceship_01_animation.png");

			m_Rect = 20;

			m_Color = BLUE;

			m_Scale = { 4.0f,3.5f };
		}
	


		//半径
		m_radius = m_Rect * m_Scale.x / 2.0f;

		//オブジェクトタイプ
		m_objType = ObjectType::ENEMY;

		//アニメーションカウンター
		m_AnimCnt = 0.0f;

		//クールタイム
		m_BulletCT = 60;

		//カウンター
		m_BulletCnt = 0;
	
}

//更新処理
void Enemy::Update()
{
	//生存していれば
	if (m_Flg == true)
	{

		m_Pos.x += m_Move.x;
		if (m_Pos.x > 640)
		{
			m_Move.x *= -1;
		}
		else if (m_Pos.x < -640)
		{
			m_Move.x *= -1;
		}

		//弾カウンターインクリメント
		m_BulletCnt++;

		//弾発射処理
		std::shared_ptr<EnemyBullet> ebullet;
		ebullet = std::make_shared<EnemyBullet>();
		if (rand() % 50 == 1)
		{
			//クールタイムを終えていれば
			if (m_BulletCnt >= m_BulletCT)
			{
				ebullet->Init();
				ebullet->SetPos(m_Pos);
				ebullet->SetColor(m_Color);
				m_BulletCnt = 0;
				SceneManager::GetInstance().AddObject(ebullet);
			}
		}


		m_AnimCnt += 0.1f;
		if (m_AnimCnt >= 4.0f)
		{
			m_AnimCnt = 0.0f;
		}
	}



	//行列
	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
	m_Mat = m_ScaleMat * m_TransMat;
}

void Enemy::Draw()
{
	if (m_Flg == true)
	{
		SHADER.m_spriteShader.SetMatrix(m_Mat);
		SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ (int)m_AnimCnt * m_Rect,0,m_Rect,23 }, m_Alpha);
	}
}

void Enemy::ImGuiUpdate()
{
	ImGui::Text(u8"EnemyPos : %f", m_Pos.x);
	ImGui::Text(u8"EnemyFlg : %d", m_Flg);
}

void Enemy::Hit()
{
	m_Flg = false;
}

void Enemy::Release()
{
	m_Tex.Release();
}
