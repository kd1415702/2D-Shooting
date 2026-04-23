#include "Game.h"
#include "../SceneManager.h"

void Game::Init()
{}

void Game::Update()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		SceneAPP.ChangeScene(TITLE);

	}
}

void Game::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "Game", Math::Color{ 1,1,1 });

	SHADER.m_spriteShader.DrawString(0, -100, "SPACE", Math::Color{ 1,1,1 });
}
