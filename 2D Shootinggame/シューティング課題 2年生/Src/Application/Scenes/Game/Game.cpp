#include "Game.h"
#include "../SceneManager.h"
#include"../../Player/Player.h"
#include"../../Object/Enemy/Enemy.h"
#include"../Title/Title.h"
#include"../../Object/Bullet/Bullet.h"
#include"../../Object/BaseObject.h"


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
	for (int i = 0; i < 2; i++)
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
}

//更新
void Game::Update()
{

	//更新処理
	if (m_Player == nullptr) { return; }

	PreUpdate();


	for (int i = 0; i < m_ObjList.size(); ++i)
	{
		m_ObjList[i]->Update();
	}

	m_Player->Update();

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





	m_BulletCntManager();

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

	//敵描画
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