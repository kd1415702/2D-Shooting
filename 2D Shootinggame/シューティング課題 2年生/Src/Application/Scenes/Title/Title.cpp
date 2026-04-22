#include "Title.h"

Title::Title()
{

}

Title::~Title()
{

}

void Title::Draw()
{
	SHADER.m_spriteShader.DrawString(0, 0, "Title", Math::Color{ 1,1,1 });
}

void Title::Update()
{

}

void Title::ChangeNowTitle(TitleType title)
{

}
