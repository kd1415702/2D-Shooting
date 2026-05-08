#include "EnemyBullet.h"
#include "../../Scenes/Game/Game.h"
#include"../../Scenes/SceneManager.h"
#include"../Enemy/Enemy.h"

//初期化
void EnemyBullet::Init()
{

	//球発生
	std::shared_ptr<Enemy> enemy;
	enemy = std::make_shared<Enemy>();

	if (enemy->GetFlg())
	{
		if (rand() % 2 == 0)
		{
			m_BulletColor = RED;
		}
		else
		{
			m_BulletColor = BLUE;
		}

		m_Pos = {};

		m_Tex.Load("Assets/Texture/Enemy/Bullet/P1_Bullet_Alt2.png");

		m_Rect = 26;
		
		m_Move = { 0.0f,-3.0f };

		m_Scale = { 3.0f,3.0f };

		m_Flg = true;

		m_radius = m_Rect * m_Scale.x / 2;

		m_Alpha = 1.0f;

		m_objType = ObjectType::ENEMYBULLET;
	}

}

void EnemyBullet::Update()
{
	if (m_Flg == true)
	{

		m_Pos.y += m_Move.y;

		if (m_Pos.y <= -360)
		{
			m_Flg = false;
		}




		m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
		m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
		m_Mat = m_ScaleMat * m_TransMat;
	}

	
}

void EnemyBullet::Draw()
{
	if (m_Flg)
	{
		if (m_BulletColor == RED)
		{
			SHADER.m_spriteShader.SetMatrix(m_Mat);
			SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 0,0,m_Rect / 2,m_Rect }, m_Alpha);
		}
		if (m_BulletColor == BLUE)
		{
			SHADER.m_spriteShader.SetMatrix(m_Mat);
			SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ 13,0,m_Rect / 2,m_Rect }, m_Alpha);
		}
	}
}

void EnemyBullet::Release()
{
	m_Tex.Release();
}
