#include "Game.h"
#include "../SceneManager.h"
#include"../../Player/Player.h"
#include"../../Enemy/Enemy.h"
#include"../Title/Title.h"
//#include"../../Hit/Hit.h"


//初期化
void Game::Init()
{
	//領域確保
	m_Player = std::make_shared<Player>();
	m_Enemy = std::make_shared<Enemy>();
	//m_Hit = std::make_shared<Hit>();

	//自機初期化
	m_Player->Init();
	m_PlayerTex.Load("Assets/Texture/Player/player.png");
	m_Player->SetTex(&m_PlayerTex);

	//敵初期化
	m_Enemy->Init();



	//m_Hit->Init();
}

//更新
void Game::Update()
{

	//更新処理
	if (m_Player == nullptr) { return; }
	if (m_Enemy == nullptr) { return; }




	m_Player->Update();

	m_Enemy->Update();



	//m_Hit->EnemyPlayerHit();

	if (m_Enemy->GetFlg())
	{
		const float x = m_Enemy->GetPos().x - m_Player->GetPos().x;
		const float y = m_Enemy->GetPos().y - m_Player->GetPos().y;
		const float z = sqrt(x * x + y * y);



		//半径＋半径
		const float sum = m_Enemy->GetRadius() + m_Player->GetRadius();

		if (z < sum)
		{

			m_Player->HitDmg();

			return;
		}

	}

		//タイトルへ戻る
		if (GetAsyncKeyState(VK_RETURN) & 0x8000)
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
	m_Enemy->Draw();

	//自機描画	
	m_Player->Draw();
	

	SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Color{ 1,1,1 });

	SHADER.m_spriteShader.DrawString(0, -100, "E", Math::Color{ 1,1,1 });
	
	
}

void Game::Release()
{
	m_PlayerTex.Release();
}

void Game::ImGuiUpdate()
{
	m_Player->ImGuiUpdate();
	m_Enemy->ImGuiUpdate();
}
