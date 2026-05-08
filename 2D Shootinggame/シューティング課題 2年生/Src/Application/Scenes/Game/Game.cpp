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
	//m_Enemy = std::make_shared<Enemy>();
	//m_Bullet = std::make_shared<Bullet>();*/
	////m_Hit = std::make_shared<Hit>();
	
	//自機初期化
	m_Player->Init();
	m_PlayerTex.Load("Assets/Texture/Player/SpaceShips_Player-0001.png");
	m_Player->SetTex(&m_PlayerTex);


	//敵初期化
	for (int i = 0; i < 3; i++)
	{
		std::shared_ptr<Enemy> enemy;
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		SceneManager::GetInstance().AddObject(enemy);
	}


	
	m_Ui = std::make_shared<Ui>();
	m_Ui->Init();

	//背景初期化
	m_BackTex.Load("Assets/Texture/Back/Background_Full-0001.png");
	m_BackMat = Math::Matrix::CreateTranslation(0, 0, 0);
}

//更新
void Game::Update()
{
	
	if (m_Player == nullptr) { return; }

	//事前更新
	PreUpdate();

	//全オブジェクト更新
	for (int i = 0; i < SceneManager::GetInstance().GetObjList().size(); ++i)
	{
		SceneManager::GetInstance().GetObjList()[i]->Update();
		
	}

	//for (int i = 0; i < m_ObjList.size(); ++i)
	//{
	//	m_ObjList[i]->Update();
	//}

	//自機更新
	m_Player->Update();

	//Ui更新
	m_Ui->Update();

	////敵弾発射処理
	//EnemyBulletAct();

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




	////弾発射
	//if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	//{
	//	if (m_BulletCnt >= m_BulletCT)
	//	{
	//		std::shared_ptr<Bullet> bullet;
	//		bullet = std::make_shared<Bullet>();

	//		//球発射
	//		bullet->Init();
	//		if(m_Player->GetColor() == RED) 
	//		{
	//			bullet->SetRect(70, 80);
	//		}
	//		if (m_Player->GetColor() == BLUE)
	//		{
	//			bullet->SetRect(70, 0);
	//		}


	//		bullet->SetFlg(true);
	//		bullet->SetPos(m_Player->GetPos());
	//		m_BulletCnt = 0;

	//		bullet->SetOwner(this);
	//		SceneManager::GetInstance().GetObjList().push_back(bullet);
	//	}
	//}


	


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
	SHADER.m_spriteShader.SetMatrix(m_BackMat);
	SHADER.m_spriteShader.DrawTex(&m_BackTex, Math::Rectangle{ 0,0,1280,720 }, 1.0f);

	//Ui
	m_Ui->Draw();

	////Ui描画
	//SHADER.m_spriteShader.SetMatrix(m_LifeMat);
	//SHADER.m_spriteShader.DrawTex(&m_LifeTex, Math::Rectangle{ 0,0,m_LifeRect,32 }, 1.0f);

	//全オブジェクト描画
	for (int i = 0; i < SceneManager::GetInstance().GetObjList().size();++i)
	{
		SceneManager::GetInstance().GetObjList()[i]->Draw();
	}

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

	//for (int i = 0; i < m_ObjList.size(); ++i)
	//{
	//	m_ObjList[i]->ImGuiUpdate();
	//}
}

void Game::PreUpdate()
{
	// //イテレータ作成 auto版
	//auto it = SceneManager::GetInstance().GetObjList().begin();

	//while (it != SceneManager::GetInstance().GetObjList().end())	// end() は 最後の要素の1個後ろを返す
	//{
	//	// オブジェクトの有効チェック
	//	if ((*it)->GetFlg() == false)
	//	{
	//		// 無効なオブジェクトをリストから削除
	//		it = SceneManager::GetInstance().GetObjList().erase(it);
	//	}
	//	else
	//	{
	//		it++;	// 次の要素へイテレータを進める
	//	}
	//}

	
}



//敵弾発射処理
//void Game::EnemyBulletAct()
//{
//
//	std::shared_ptr<EnemyBullet> ebullet;
//	ebullet = std::make_shared<EnemyBullet>();
//
//	if (rand() % 50 == 1)
//	{
//		ebullet->SetOwner(this);
//		ebullet->Init();
//		m_ObjList.push_back(ebullet);
//	}
//
//
//}
