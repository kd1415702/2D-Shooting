#include "Title.h"
#include "../SceneManager.h"

Title::Title()
{

}

Title::~Title()
{

}

void Title::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "Title", Math::Color{ 1,1,1 });

	SHADER.m_spriteShader.DrawString(0, -100, "Enter", Math::Color{ 1,1,1 });
}

void Title::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		SceneAPP.ChangeScene(GAME);
	
	}
}


