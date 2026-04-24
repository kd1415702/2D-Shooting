#include "Game.h"
#include "../SceneManager.h"
#include"../../Player/Player.h"

void Game::Init()
{
	//領域確保
	m_Player = std::make_shared<Player>();

	m_Player->Init();
	m_PlayerTex.Load("Assets/Texture/Player/player.png");
	m_Player->SetTex(&m_PlayerTex);
}

void Game::Update()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		
		SceneAPP.ChangeScene(TITLE);

	}

	m_Player->Update();
}

void Game::Draw()
{

	m_Player->Draw();

	SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Color{ 1,1,1 });

	SHADER.m_spriteShader.DrawString(0, -100, "SPACE", Math::Color{ 1,1,1 });
	
	
}

void Game::Release()
{
	m_PlayerTex.Release();
}
