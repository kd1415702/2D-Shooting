#include "Game.h"
#include "../SceneManager.h"
#include"../../Player/Player.h"
#include"../../Object/Enemy/Enemy.h"
#include"../Title/Title.h"
#include"../../Object/Bullet/Bullet.h"
#include"../../Object/EnemyBullet/EnemyBullet.h"


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
	m_PlayerTex.Load("Assets/Texture/Player/Spaceships.png");
	m_Player->SetTex(&m_PlayerTex);

	//敵初期化
	std::shared_ptr<Enemy> enemy;
	for (int i = 0; i < 10; i++)
	{
		enemy = std::make_shared<Enemy>();
		enemy->Init();
		m_ObjList.push_back(enemy);
	}

	//弾初期化
	std::shared_ptr<Bullet> bullet;
	bullet = std::make_shared<Bullet>();
	bullet->Init();
	bullet->SetOwner(this);
	m_ObjList.push_back(bullet);

	m_BulletCnt = 11;

	//敵弾初期化
	//std::shared_ptr<EnemyBullet> ebullet;
	//ebullet = std::make_shared<EnemyBullet>();
	//ebullet->SetOwner(this);
	//m_ObjList.push_back(ebullet);
}

//更新
void Game::Update()
{
	
	if (m_Player == nullptr) { return; }

	//事前更新
	PreUpdate();

	//全オブジェクト更新
	for (int i = 0; i < m_ObjList.size(); ++i)
	{
		m_ObjList[i]->Update();
	}

	//自機更新
	m_Player->Update();
	
	//自機弾発射マネージャー
	m_BulletCntManager();

	//敵弾発射処理
	EnemyBulletAct();

	//敵との当たり判定
	for (auto obj : m_ObjList)
	{
		if (obj->GetObjType() == ObjectType::ENEMY)
		{
			Math::Vector2 v;
			v = obj->GetPos() - m_Player->GetPos();

			if (v.Length() < m_Player->GetRadius())
			{
				m_Player->HitDmg();
			}
		}
	}

	//敵弾との当たり判定
	for (auto obj : m_ObjList)
	{
		if (obj->GetObjType() == ObjectType::ENEMYBULLET)
		{
			Math::Vector2 v;
			v = obj->GetPos() - m_Player->GetPos();

			if (v.Length() < m_Player->GetRadius())
			{
				//弾が赤の場合
				if (obj->GetColor() == RED)
				{
					//弾と同じ色なら
					if (m_Player->GetColor() == RED)
					{
						//経験値ゲット
						m_Player->SetExp(10);
						obj->SetFlg(false);
					}
					//弾と違う色なら
					else if (m_Player->GetColor() == BLUE)
					{
						//ダメージ
						m_Player->HitDmg();
						obj->SetFlg(false);
					}
				}
				//弾が青の場合
				else if (obj->GetColor() == BLUE)
				{
					//弾と違う色なら
					if (m_Player->GetColor() == RED)
					{
						//ダメージ
						m_Player->HitDmg();
						obj->SetFlg(false);
					}
					//弾と同じ色なら
					else if (m_Player->GetColor() == BLUE)
					{
						//経験値ゲット
						m_Player->SetExp(10);
						obj->SetFlg(false);
					}
				}
			}
		}
	}




	//弾発射
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		if (m_BulletCnt >= m_BulletCT)
		{
			std::shared_ptr<Bullet> bullet;
			bullet = std::make_shared<Bullet>();

			//球発射
			bullet->Init();
			bullet->SetFlg(true);
			bullet->SetPos(m_Player->GetPos());
			m_BulletCnt = 0;

			bullet->SetOwner(this);
			m_ObjList.push_back(bullet);
		}
	}


	//m_Hit->EnemyPlayerHit();

	//if (m_Enemy->GetFlg())
	//{
	//	const float x = m_Enemy->GetPos().x - m_Player->GetPos().x;
	//	const float y = m_Enemy->GetPos().y - m_Player->GetPos().y;
	//	const float z = sqrt(x * x + y * y);



	//	//半径＋半径
	//	const float sum = m_Enemy->GetRadius() + m_Player->GetRadius();

	//	if (z < sum)
	//	{

	//		m_Player->HitDmg();

	//		return;
	//	}


		//タイトルへ戻る
		if (GetAsyncKeyState('E') & 0x8000)
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






}


//描画  

//順番は敵→弾→自機
void Game::Draw()
{
	if(m_Player == nullptr){return;}

	//全オブジェクト描画
	for (int i = 0; i < m_ObjList.size(); ++i)
	{
		m_ObjList[i]->Draw();
	}


	//自機描画	
	m_Player->Draw();
	

	//SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Color{ 1,1,1 });

	//SHADER.m_spriteShader.DrawString(0, -100, "SPACE", Math::Color{ 1,1,1 });
	
	
}

void Game::Release()
{
	m_PlayerTex.Release();

	for (int i = 0; i < m_ObjList.size(); ++i)
	{
		m_ObjList.clear();
	}
}

void Game::ImGuiUpdate()
{
	m_Player->ImGuiUpdate();
	for (int i = 0; i < m_ObjList.size();++i)
	{
		m_ObjList[i]->ImGuiUpdate();
	}
}

void Game::PreUpdate()
{
	// イテレータ作成 auto版
	auto it = m_ObjList.begin();

	while (it != m_ObjList.end())	// end() は 最後の要素の1個後ろを返す
	{
		// オブジェクトの有効チェック
		if ((*it)->GetFlg() == false)
		{
			// 無効なオブジェクトをリストから削除
			it = m_ObjList.erase(it);
		}
		else
		{
			it++;	// 次の要素へイテレータを進める
		}
	}
}

void Game::BulletAct()
{

	if (m_BulletCnt >= m_BulletCT)
	{
		std::shared_ptr<Bullet> bullet;
		bullet = std::make_shared<Bullet>();


		m_BulletCnt = 0;
	}
}

void Game::m_BulletCntManager()
{
	m_BulletCnt++;
}

//敵弾発射処理
void Game::EnemyBulletAct()
{
	std::shared_ptr<Enemy> enemy;
	enemy = std::make_shared<Enemy>();

	std::shared_ptr<EnemyBullet> ebullet;
	ebullet = std::make_shared<EnemyBullet>();

	if (rand() % 50 == 1)
	{
		ebullet->SetOwner(this);
		ebullet->Init();
		m_ObjList.push_back(ebullet);
	}
}
