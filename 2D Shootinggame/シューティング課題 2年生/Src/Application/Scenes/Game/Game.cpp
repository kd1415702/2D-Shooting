#include "Game.h"
#include "../SceneManager.h"
#include"../../Player/Player.h"

void Game::Init()
{
	//領域確保
	m_Player = std::make_shared<Player>();

	/*m_Player = new Player();*/

	//自機初期化
	m_Player->Init();
	m_PlayerTex.Load("Assets/Texture/Player/player.png");
	m_Player->SetTex(&m_PlayerTex);
}

void Game::Update()
{
	//更新処理
	if (m_Player == nullptr)return;

	m_Player->Update();



	//タイトルへ戻る
	if (GetAsyncKeyState(VK_SPACE))
	{	
		SceneAPP.ChangeScene(TITLE);

	}




	
}

void Game::Draw()
{

	//描画	
	m_Player->Draw();

	SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Color{ 1,1,1 });

	SHADER.m_spriteShader.DrawString(0, -100, "SPACE", Math::Color{ 1,1,1 });
	
	
}

void Game::Release()
{
	//解放
	m_PlayerTex.Release();
}
