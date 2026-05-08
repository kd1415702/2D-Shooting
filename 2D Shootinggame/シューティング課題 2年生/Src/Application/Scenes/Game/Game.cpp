#include "Game.h"
#include "../SceneManager.h"
#include"../../Player/Player.h"
#include"../../Object/Enemy/Enemy.h"
#include"../Title/Title.h"
#include"../../Object/Bullet/Bullet.h"
#include"../../Object/EnemyBullet/EnemyBullet.h"
#include"../../Ui/Ui.h"


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
	m_PlayerTex.Load("Assets/Texture/Player/SpaceShips_Player-0001_2.png");
	m_Player->SetTex(&m_PlayerTex);



	//敵初期化
	for (int i = 0; i < 4; i++)
	{
		std::shared_ptr<Enemy> enemy;
		enemy = std::make_shared<Enemy>();
		enemy->Init();

		

		SceneManager::GetInstance().AddObject(enemy);
	}


	//Ui初期化
	m_Ui->Init();

	//背景ロード
	m_BackTex.Load("Assets/Texture/Back/Background_SmallStars-0001.png");
	m_BackPos[0] = 0.0f;
	m_BackPos[1] = 720.0f;

	m_BackTex2.Load("Assets/Texture/Back/Black.png");
	m_BackMat2 = Math::Matrix::CreateTranslation(0, -310.0f, 0);
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
	m_Ui->Update();


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
	//m_BackPos[0] -= 3.0f;
	//if(m_BackPos[0] >= -720.0f)
	//{
	//	m_BackPos[0] = 720.0f;
	//}

	//m_BackPos[1] -= 3.0f;


	//if (m_BackPos[1] >= -720.0f)
	//{
	//	m_BackPos[1] = 720.0f;
	//}

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

				if (v.Length() < m_Player->GetRadius())
				{
					obj->SetFlg(false);
					//弾が赤の場合
					if (obj->GetColor() == RED)
					{
						//弾と同じ色なら
						if (m_Player->GetColor() == RED)
						{
							//経験値ゲット
							m_Player->SetExp(10);

						}
						//弾と違う色なら
						else if (m_Player->GetColor() == BLUE)
						{
							//ダメージ
							m_Player->HitDmg();
						}

						SceneManager::GetInstance().GetObjList().clear();
						return;
					}
					//弾が青の場合
					else if (obj->GetColor() == BLUE)
					{
						//弾と違う色なら
						if (m_Player->GetColor() == RED)
						{
							//ダメージ
							m_Player->HitDmg();
						}
						//弾と同じ色なら
						else if (m_Player->GetColor() == BLUE)
						{
							//経験値ゲット
							m_Player->SetExp(10);
						}

						SceneManager::GetInstance().GetObjList().clear();
						return;
					}
				}
			}
		}
	}

	


		//タイトルへ戻る
		//if (GetAsyncKeyState('E') & 0x8000)
		//{
		//	if (m_KeyFlg == false)
		//	{
		//		SceneAPP.ChangeScene(TITLE);
		//		m_KeyFlg = true;
		//	}
		//}
		//else
		//{
		//	m_KeyFlg = false;
		//}






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

	//for (int i = 0; i < m_ObjList.size(); ++i)
	//{
	//	m_ObjList[i]->Draw();
	//}

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
	m_Player->ImGuiUpdate();

	for (int i = 0; i < SceneManager::GetInstance().GetObjList().size();++i)
	{
		SceneManager::GetInstance().GetObjList()[i]->ImGuiUpdate();
	}


}






