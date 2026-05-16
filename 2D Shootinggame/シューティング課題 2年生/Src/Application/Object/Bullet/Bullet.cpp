#include "Bullet.h"
#include "../../Scenes/Game/Game.h"
#include"../../Player/Player.h"
#include"../../Scenes/SceneManager.h"
#include"../Enemy/Enemy.h"

void Bullet::Init()
{

	m_Player = m_Player = std::make_shared<Player>();


	/*m_Pos = { };*/

	//m_Move = { 0.0f,5.0f };

	m_Flg = true;

	m_Rect = 10;

	m_Scale = { 2.0f,2.0f };

	m_radius = m_Rect * m_Scale.x / 2;

	m_objType = ObjectType::BULLET;

	m_Tex.Load("Assets/Texture/Bullet/FoxShotSheet.png");

	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(0, 0, 0);
	m_Mat = m_ScaleMat * m_TransMat;

}

void Bullet::Update()
{
	if (m_Flg == true)
	{
		m_Pos += m_Move;

		if (m_Pos.y > 360 || m_Pos.x < -640 || m_Pos.x > 640)
		{
			m_Flg = false;
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


	}
	m_TransMat = Math::Matrix::CreateTranslation(m_Pos.x, m_Pos.y, 0);
	m_ScaleMat = Math::Matrix::CreateScale(m_Scale.x, m_Scale.y, 0);
	m_Mat = m_ScaleMat * m_TransMat;

}

void Bullet::Draw()
{
	if (m_Flg == true)
	{
		SHADER.m_spriteShader.SetMatrix(m_Mat);
		SHADER.m_spriteShader.DrawTex(&m_Tex, Math::Rectangle{ m_RectX,m_RectY,m_Rect,m_Rect }, 1.0f);
	}
}



void Bullet::Release()
{
	m_Tex.Release();
}
