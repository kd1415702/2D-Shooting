#include "Game.h"
#include "../SceneManager.h"
#include"../../Player/Player.h"
#include"../../Object/Enemy/Enemy.h"
#include"../Title/Title.h"
#include"../../Object/Bullet/Bullet.h"
#include"../../Object/EnemyBullet/EnemyBullet.h"
#include"../../Ui/Ui.h"
#include"../../Object/BossEnemy/BossEnemy.h"
#include"../../Object/BossEnemyBullet/BossEnemyBullet.h"


//初期化
void Game::Init()
{
	

	//乱数初期化
	srand(time(0));

	//領域確保
	m_Player = std::make_shared<Player>();
	m_Ui = std::make_shared<Ui>();
	

	//自機初期化
	m_Player->Init();
	m_PlayerTex.Load("Assets/Texture/Player/PlayerBlue.png");
	m_Player->SetTex(&m_PlayerTex);




	
	////ボス初期化
	//std::shared_ptr<BossEnemy> boss;
	//boss = std::make_shared<BossEnemy>();
	//boss->Init();
	//boss->SetPos({ 0.0f,400.0f });
	//boss->SetMove({ 0.0f,-2.0f });
	//SceneManager::GetInstance().AddObject(boss);
	//m_BossFlg = true;


	//Ui初期化
	m_Ui->Init();

	//背景ロード
	m_BackTex.Load("Assets/Texture/Back/Background_SmallStars-0001.png");
	m_BackPos[0] = 0.0f;
	m_BackPos[1] = 720.0f;

	

	m_BackTex2.Load("Assets/Texture/Back/Black.png");
	m_BackMat2 = Math::Matrix::CreateTranslation(0, -310.0f, 0);

	//m_WaveFlg[0] = false;
	m_Wave = WAVE1;
}

//更新
void Game::Update()
{
	
	if (m_Player == nullptr) { return; }


	//全オブジェクト更新
	for (int i = 0; i < SceneManager::GetInstance().GetObjList().size(); ++i)
	{
		SceneManager::GetInstance().GetObjList()[i]->Update();
		
	}

	//自機更新
	m_Player->Update();


	//Ui更新
	m_Ui->SetExp(m_Player->GetExp());
	m_Ui->SetLv(m_Player->GetLv());
	m_Ui->Update();

	WaveManager();

	
	//残り体力表示処理
	switch (m_Player->GetHp())
	{
	case 3:
		m_Ui->SetRect(64 * 3);
		break;

	case 2:
		m_Ui->SetRect(64 * 2);
		break;

	case 1:
		m_Ui->SetRect(64 * 1);
		break;

	default:
		m_Ui->SetRect(0);
		break;
	}

	//背景更新処理
	for (int i = 0; i < BackNum; i++)
	{
		m_BackPos[i] -= 3.0f;
		if (m_BackPos[i] <= -720.0f)
		{
			m_BackPos[i] = 720.0f;
		}
	}

	for (int i = 0; i < BackNum; i++)
	{
		m_BackMat[i] = Math::Matrix::CreateTranslation(0, m_BackPos[i], 0);
	}

	//敵との当たり判定
	for (auto obj : SceneManager::GetInstance().GetObjList())
	{
		if (obj->GetObjType() == ObjectType::ENEMY)
		{
			if (obj->GetFlg() == true)
			{
				Math::Vector2 v;
				v = obj->GetPos() - m_Player->GetPos();

				if (v.Length() < m_Player->GetRadius())
				{
					m_Player->HitDmg();
				}
			}
		}
	}

	//敵弾との当たり判定
	for (auto obj : SceneManager::GetInstance().GetObjList())
	{
		if (obj->GetObjType() == ObjectType::ENEMYBULLET)
		{
			if (obj->GetFlg())
			{
				std::shared_ptr<Enemy> ebullet;
				ebullet = std::make_shared<Enemy>();

				Math::Vector2 v;
				v = obj->GetPos() - m_Player->GetPos();

				if (obj->GetColor() == m_Player->GetColor())
				{

					if (v.Length() < m_Player->GetRadius() + m_Player->GetBulletAbsorbRange())
					{
						obj->SetFlg(false);
						m_Player->SetExp(10);

					}

				}
				else
				{
					if (v.Length() < m_Player->GetRadius())
					{
						obj->SetFlg(false);
						m_Player->HitDmg();
					}
				}
			}
		}
	}


	//ボスとの当たり判定
	for (auto obj : SceneManager::GetInstance().GetObjList())
	{
		if (obj->GetObjType() == ObjectType::BOSSENEMY)
		{
			if (obj->GetFlg() == true)
			{
				Math::Vector2 v;
				v = obj->GetPos() - m_Player->GetPos();

				if (v.Length() < m_Player->GetRadius())
				{
					m_Player->HitDmg();
				}
			}
		}
	}


	//m_BulletCnt++;
	////ボス弾発生
	//if (rand() % 30 == 0)
	//{
	//	if (m_BulletCnt >= m_BulletCT)
	//	{
	//		m_BulletCnt = 0;

	//		std::shared_ptr<BossEnemyBullet> bossbullet;
	//		bossbullet = std::make_shared<BossEnemyBullet>();

	//		bossbullet->Init();
	//		/*bossbullet->SetPos({ 0.0f,0.0f });*/
	//		bossbullet->SetMove({ 0.0f,-2.0f });
	//		SceneManager::GetInstance().AddObject(bossbullet);
	//	}
	//}

	
	//ボスの弾との当たり判定
	for (auto obj : SceneManager::GetInstance().GetObjList())
	{
		if (obj->GetObjType() == ObjectType::BOSSENEMYBULLET)
		{
			if (obj->GetFlg() == true)
			{
				std::shared_ptr<BossEnemyBullet> bossbullet;
				bossbullet = std::make_shared<BossEnemyBullet>();
				Math::Vector2 v;
				v = obj->GetPos() - m_Player->GetPos();

					if (obj->GetColor() == m_Player->GetColor())
					{
						if (v.Length() < m_Player->GetRadius() + m_Player->GetBulletAbsorbRange())
						{
							obj->SetFlg(false);
							m_Player->SetExp(10);
						}
						
					}
					else
					{
						if (v.Length() < m_Player->GetRadius() + obj->GetRadius())
						{
							obj->SetFlg(false);
							m_Player->HitDmg();
						}
					}
			}
				
		}
	}


	//if (m_BossFlg == true)
	//{
	//	std::shared_ptr<BossEnemy> boss;
	//	boss = std::make_shared<BossEnemy>();

	//	if (boss->GetFlg() == false)
	//	{
	//		SceneManager::GetInstance().ChangeScene(TITLE);
	//	}

	//}

		//タイトルへ戻る
		if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		{
			if (m_KeyFlg == false)
			{
				SceneAPP.ChangeScene(TITLE);
				m_KeyFlg = true;
			}
		}
		else
		{
			m_KeyFlg = false;
		}

		if (GetAsyncKeyState('5') & 0x8000)
		{
			m_Wave = WAVE5;
		}


}







//描画  

//順番は敵→弾→自機
void Game::Draw()
{
	if(m_Player == nullptr){return;}

	//背景
	for (int i = 0; i < BackNum; i++)
	{
		SHADER.m_spriteShader.SetMatrix(m_BackMat[i]);
		SHADER.m_spriteShader.DrawTex(&m_BackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);
	}

	//全オブジェクト描画
	for (int i = 0; i < SceneManager::GetInstance().GetObjList().size();++i)
	{
		SceneManager::GetInstance().GetObjList()[i]->Draw();
	}


	//黒帯
	SHADER.m_spriteShader.SetMatrix(m_BackMat2);
	SHADER.m_spriteShader.DrawTex(&m_BackTex2, Math::Rectangle{ 0,0,1280,100 }, 1.0f);

	//Ui
	m_Ui->Draw();
	

	//自機描画	
	m_Player->Draw();
	
	
	
}

void Game::Release()
{
	m_PlayerTex.Release();
	m_BackTex.Release();

	SceneManager::GetInstance().GetObjList().clear();


}

void Game::ImGuiUpdate()
{
	/*m_Player->ImGuiUpdate();

	for (int i = 0; i < SceneManager::GetInstance().GetObjList().size();++i)
	{
		SceneManager::GetInstance().GetObjList()[i]->ImGuiUpdate();
	}*/
	ImGui::Text(u8"Wave1Cnt : %d", m_Wave1Cnt);
	ImGui::Text(u8"Wave2Cnt : %d", m_Wave2Cnt);
	ImGui::Text(u8"Wave3Cnt : %d", m_Wave3Cnt);
	ImGui::Text(u8"Wave4Cnt : %d", m_Wave4Cnt);
	ImGui::Text(u8"Wave5Cnt : %d", m_Wave5Cnt);


}

void Game::WaveManager()
{
	
	//ウェーブ1=======================-
	if (m_Wave == WAVE1)
	{
		if (m_Wave1Flg == false)
		{
			//敵初期化
			for (int i = 0; i < 4; i++)
			{
				std::shared_ptr<Enemy> enemy;
				enemy = std::make_shared<Enemy>();


				enemy->Init();
				enemy->SetPos({ 700.0f + i * 200,200.0f });
				enemy->SetMove({ -1.0f,0 });

				SceneManager::GetInstance().AddObject(enemy);
			}
			m_Wave1Flg = true;
		}
	}
	if (m_Wave1Flg == true)
	{
		m_Wave1Cnt++;
		if (m_Wave1Cnt >= 1500)
		{
			m_Wave = WAVE2;
		}
	}

	//====================================---

	//ウェーブ2================================-
	if (m_Wave == WAVE2)
	{
		if (m_Wave2Flg == false)
		{
			for (int i = 0; i < 5; i++)
			{
				std::shared_ptr<Enemy> enemy;
				enemy = std::make_shared<Enemy>();


				enemy->Init();
				enemy->SetPos({ -700.0f - i * 200,200.0f });
				enemy->SetMove({ 1.5f,0.0f });
				
				SceneManager::GetInstance().AddObject(enemy);
			}
			m_Wave2Flg = true;
		}

		if (m_Wave1Flg == true)
		{
			m_Wave2Cnt++;
			if (m_Wave2Cnt >= 1200)
			{
				m_Wave = WAVE3;
			}
		}
	}
	//================================================

	//ウェーブ3=====================================
	if (m_Wave == WAVE3)
	{
		if (m_Wave3Flg == false)
		{
			for (int i = 0; i < 3; i++)
			{
				std::shared_ptr<Enemy> enemy;
				enemy = std::make_shared<Enemy>();


				enemy->Init();
				enemy->SetPos({ -200.0f - i * 150,400.0f + i * 150.0f });
				enemy->SetMove({ 0.0f,-1.0f });
				enemy->SetBulletCT(60);
				SceneManager::GetInstance().AddObject(enemy);
			}

			for (int i = 0; i < 3; i++)
			{
				std::shared_ptr<Enemy> enemy;
				enemy = std::make_shared<Enemy>();


				enemy->Init();
				enemy->SetPos({ 200.0f + i * 150,400.0f + i * 150.0f });
				enemy->SetMove({ 0.0f,-1.0f });
				enemy->SetBulletCT(60);
				SceneManager::GetInstance().AddObject(enemy);
			}

			m_Wave3Flg = true;
		}
	}

	if (m_Wave3Flg == true)
	{
		m_Wave3Cnt++;
		if (m_Wave3Cnt >= 1000)
		{
			m_Wave = WAVE4;
		}
	}
	//====================================


	//ウェーブ4=========================
	if (m_Wave == WAVE4)
	{
		if (m_Wave4Flg == false)
		{
			
			for (int i = 0; i < 3; i++)
			{
				std::shared_ptr<Enemy> enemy;
				enemy = std::make_shared<Enemy>();

				enemy->Init();
				enemy->SetPos({ 700.0f + i * 150,-100.0f });
				enemy->SetMove({ -1.5f,0.0f });

				SceneManager::GetInstance().AddObject(enemy);
			}

			for (int i = 0; i < 4; i++)
			{
				std::shared_ptr<Enemy> enemy;
				enemy = std::make_shared<Enemy>();

				enemy->Init();
				enemy->SetPos({ -700.0f - i * 150,100.0f });
				enemy->SetMove({ 1.5f,0.0f });

				SceneManager::GetInstance().AddObject(enemy);
			}

			for (int i = 0; i < 3; i++)
			{
				std::shared_ptr<Enemy> enemy;
				enemy = std::make_shared<Enemy>();

				enemy->Init();
				enemy->SetPos({ 800.0f + i * 150,200.0f });
				enemy->SetMove({ -1.5f,0.0f });

				SceneManager::GetInstance().AddObject(enemy);
			}

			m_Wave4Flg = true;
		}

		if (m_Wave4Flg == true)
		{
			m_Wave4Cnt++;
			if (m_Wave4Cnt >= 1300)
			{
				m_Wave = WAVE5;
			}
		}
	}

	//==============================================


	//ウェーブ5============================-
	if (m_Wave == WAVE5)
	{
		if (m_Wave5Flg == false)
		{
			//ボス初期化
			std::shared_ptr<BossEnemy> boss;
			boss = std::make_shared<BossEnemy>();
			boss->Init();
			boss->SetPos({ 0.0f,500.0f });
			boss->SetMove({ 0.0f,-2.0f });
			SceneManager::GetInstance().AddObject(boss);
			m_Wave5Flg = true;
		}

		
		
	}


}






